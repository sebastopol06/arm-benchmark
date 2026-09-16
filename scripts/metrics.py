# Usage: python3 scripts/metrics.py logs/v*.log

import re, sys
from pathlib import Path

SAMPLES = 4

def metrics(filename):
    text = Path(filename).read_text()

    # Block RThroughput
    rt = float(
        re.search(r"Block RThroughput:\s*([\d.]+)", text).group(1)
    )

    # LLVM-MCA Average Wait Times <total>:
    #
    # [0] Executions
    # [1] Scheduler queue wait
    # [2] Scheduler queue wait while ready
    # [3] WB -> Retire
    m = re.search(
        r"^\s*\d+\s+([\d.]+)\s+([\d.]+)\s+([\d.]+)\s+<total>",
        text,
        re.MULTILINE
    )

    if not m:
        raise RuntimeError(f"Cannot find Average Wait Times <total> in {filename}")

    wait_scheduler = float(m.group(1))  # [1]
    wait_ready     = float(m.group(2))  # [2]
    wait_retire    = float(m.group(3))  # [3]

    # First LLVM-MCA timeline iteration
    timeline = []
    for line in text.splitlines():
        m = re.search(r"\[0,\d+\]\s+([.D=eE\-R]+)", line)
        if m:
            timeline.append(m.group(1))

    if not timeline:
        raise RuntimeError(f"Cannot find timeline in {filename}")

    ncycles = max(map(len, timeline))

    # PUE: fraction of timeline cycles with >= 1 executing instruction
    active_cycles = sum(
        any(c < len(row) and row[c] == "e" for row in timeline)
        for c in range(ncycles)
    )
    pue = active_cycles / ncycles

    # ED: average number of simultaneously executing instructions
    e = sum(row.count("e") for row in timeline)
    ed = e / ncycles

    return {
        "wait_scheduler": wait_scheduler,
        "wait_ready": wait_ready,
        "wait_retire": wait_retire,
        "cycles": rt / SAMPLES,
        "pue": pue,
        "ed": ed,
    }


files = sys.argv[1:]

order = {
    "v1": 1,
    "v2": 2,
    "v3": 3,
    "v4": 4,
    "v4.1": 5,
    "v5": 6,
}

files.sort(key=lambda f: order.get(Path(f).stem, 999))

names = {
    "v1":   "v1 Scalar",
    "v2":   "v2 Auto-SIMD",
    "v3":   "v3 NEON",
    "v4":   "v4 SVE",
    "v4.1": "v4.1 SVE FCMLA",
    "v5":   "v5 SME*",
}

results = [
    (names.get(Path(f).stem, Path(f).stem), metrics(f))
    for f in files
]

# Markdown header
print("| Metric | " +
      " | ".join(name for name, _ in results) + " |")
print("|---|" + "---:|" * len(results))

rows = [
    ("[1] Scheduler wait",
     lambda x: f"{x['wait_scheduler']:.1f}"),

    ("[2] Ready/resource wait",
     lambda x: f"{x['wait_ready']:.1f}"),

    ("[3] WB → Retire",
     lambda x: f"{x['wait_retire']:.1f}"),

    ("Cycles/sample",
     lambda x: f"{x['cycles']:.2f}"),

    ("PUE",
     lambda x: f"{x['pue']:.1f}"),

    ("ED",
     lambda x: f"{x['ed']:.2f}"),
]

for label, fmt in rows:
    print(
        "| " + label + " | " +
        " | ".join(fmt(x) for _, x in results) +
        " |"
    )