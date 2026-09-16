# ARM Pipeline Exploration on Toy Example

Consider different ARM implementations of a 4-Rx Maximum Ratio Combining (MRC) on the CPU pipeline. Call it a kernel.

Consider Neoverse V2, modern ARMv9 core.

Consider Godbolt framework for fast prototyping. See [▶ Open the MRC benchmark in Compiler Explorer](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQBnZJ2p4gfQ4EmDdD1QNMAOmQAHWaSoSCAZW70QARgAsi5QFUOmAAoAPEAHIADBdIArELt4NQyAKQAmAEKevpWSKYAHKs7Fw8fDLypEb0yAR4EpSM6ADCqLQAriwMIB6kKQAyeJJB2QBGmMQgAKwAHP6oHISJDOlZOXmNzQkSxaUVVbUNsZjxrSrCxATt2bmaMZhxvQyTfAT9wYPVC0Lrs527UxslWyyVOwCUMaiZxMjsFp4AzCXIWVgA1G7PqchC6CwVB%2B2DcVgAgmDwUJiJl4p90ixZPRTN8AOw%2BCGfbGfKi0VBMAifYiYH6Y8E43H4wmfPAsMlQtxogAiZO%2BEKhAHpOZ9tABaABKqIAskxTHTsp8BYTEgjUOcSiVgFzOSrPrcCG4al4ANZa5nfZ4GjjZfhMT5oBh2CAILVeJj6u16mrMy6fABUxNMdodLqdjoh3LVEHNfM%2BdnKlwgyG%2B3nD6EuauxJJ4hoNTBjvk%2B5XQSdpLCYwDTnyY6E%2BYfK7kDqoh/DNBAIxDw5UyBEwdagDFQJVop0uiYhADdu2WWPdtPxyvjkDr%2BCxuBAoZTLUI5UiUZ66ySYXh4cRTFZSJ9uZ8gqgS72mM0XNnMAQAO6YRhew9ehZe/Je55HhCvhDvhBPwQb8S1EdVW0%2BIhPlkYhUDbeExGEJccRXIlEWRTBTE3fht0bXciX3BZkOxVC1wwrDPi3TAdz3Ux8mIi0JFXdCN0onDqLw2jvwY0iWMw7DcKbeFf1IHimLQ%2BVyIEjihKJf9RKxFDxLI1iqJouT6MUkjlL4ii1M4uTuK0lT%2BLYwT8PAggB0hDEGJPABJDgMkJTBPhUezhQNNAsAYq8WE%2BYdeASehFw8DwXk%2BQpCgANWFPlhVScE%2BS8bAAHF7KCT4x2QCcp1QGdPA8RNnnJBilGIT4IABEBODwAAvdsiR1YsrDZZqflSXk2V8XwdWsykmXJSllx0ySUWJKxi33VrtWdZkj2ITQptMTR/RdBaPGW8LZv1BbnmW541tZEqGJGhhmLGzCLUmn4DV/I6j2QJbbs%2Bf8HotTaXsA97kH2r7Dp2v0To5YzKTxAkiQzZB2JaqQrCoI8of4OlYfhhkQYpYbsRPS1rV/N1PWm06cSRklYx8I1rqkMnCasanXKzZA6ZR2mpDpdHMaxpGUZ6ymmfpj0JrZ/yw35lmhZJDniexnlcZtTQCbfaWS2QaGyd5rzNAFwmtfVuMnuFwXFuFjmsexbn/I1i1ddcnXDdFrXxeNyXgchUGcRxiQ8aKo26OV0mGe8F7kA8bXiVDvWvA%2Bw3CdD9nXbNlXoZ5oO%2BYj23w/t6OnfTqX3ZlxirRtZ5Ff3Q786TmGrd%2BsPiGeAXGfrp2m/pBOzYt8ng/rmniRb8sLT7wnu9JV3lY1I7i0GgPEdV5H6RZU2cSZVkMcpPyAuc4LMFC8KPH2qLYvixK%2BWwIIDWy3Lpz1MLitKlkLGuWhLBqWxcmsWxUE4dRIjkBQCEsGw1wbQoAwDgfARAyAUGoHQRgoRLCaFsEoBgqh1DsB0HoZBhgTDmHfvYLQpBnCuB6t4fwgQQhsBAJICQUQFCjHGEkCAKQDi5GeLoIopwyjnCGJoGo3QWgSGYSAVhfCVibE4RcLQvC6ErDWNMQRwjpETGOGI7YkiYjHHkboPY0wVFcJ2DUa4Tk7gPEsC8N4HwGa/D4CwfgVCGBSFtM8UEGMYRwgkuuK6g0yrUgIiPIaOJwY0njnfY6pVaz1jwi2NsHYIBdh7H2ayw48CjnHLYzAEhFzGV4pdPS7F1IvgUpzQuF0PG5PMrRIiWTRqlOkvk/cmkinZJqWZGSFky6FLOiUqSLT8kiTEuddx3T9KyVepUxp1Shl5IMq9BpnTBmqSmSM4CHScS6VqdMjU1kvHGXXoFGUIVCoRQPnFBKSUUrpUyhfNJEhCq30ZMZE8hQCRlm0IxUpnwOCsAwhwXEsF/KYAzAgUCbYGDMCkHZHkg5aDoA8AAR0%2BFgPkJQ2zEHoEwQc1FPjglQCodEXgSTkHngafAJJ4i0AAJ60mQZ/CFOJBw8DtDNA0L1BokkPCSBYJJ8gkkOgvB5PJsT0toHaVaLpJ4YjpIeOkCw6T5DpLyle4yBlUghs8DwphtB0X4ARG6lMoUwthfwKgaqIAkmRVUGCd5%2BDcCEB1UigSCDuhBKag8/ZF7aWVQ6tVGqtUEWenq6FcKjUmrNcgi1JICDWqvJqX49qfFOqcS6hWdyqmep8d6zVHhtXh2LPqoNxqPCmswOa4glrI02pjX8ZSDqE3YBdUVFNSrVxevVZm7Nddc2BsNQWotJay1RttbG6t8bnVlzdaPVNzb02tt9ddTtBrg2FtDSi/tFa7XDohrWm0Vhx3%2BI9VO1VM6s1EievO/NIbi1htLRGgdla42budf%2BXd/SD2EgzbOkOZ7u0Xr7TetdQ600PsTYBZ9k6iQtp9cegeX7F29qvau6N67AOEi3cBUDbsimeyLggUu3jD0auzQHXNLBMi0G/YW/mQrGW7SFlR7UTLG1r1nurPVVACzkZDMxzAj06Z0a8KK%2BatGGXagE42vDb7W2EdnjzPVJGyOwco8JrwTKFq8aU6J91lcZMGkHGxjgHGLY8akHxgTqnjNKYY3nIpRGXq6fY7B6e1tzPCvozR42fHLNt3Nlx3NbGmAGa449LWJm3PBfU/qMTOzpOW1Y/ZnthmnMedC85kVEXNMd1s3pgLycWBBZSyJ5LSWXSResz5zLcWTWOZDvl5TbnQ5FddOlsrsX/MOcC9HEL61M6dcaxO0rOXfMVcLQl6rDWNo1Y015rTMWdNZbazlx69XwtdeIEtlztXitWaY2rSxs2hucZ249euY3e41c83uyuLG9utfi%2B1muPW9oTbS317bc9Bs3cq9Fo7Z23PHeW71i7GXYv6fm3Pb7D3TsNZK5SE8ApMBIqvWijFeKCXsxZLiEgJlUTYtxRqWQrZwXGQg223xJpaAxou9uUjBAftipegHTTVPydPbp5TC2W26VCHPUuy9K6/2Id%2BDW51myFrUWp9DkmHB/J7K3jvI5MUTnH1PufVJdjblS3vo/Z%2Br8AEf0oek%2Bxv9SD/3fkApA3kwGEBIOQSgNB6DMAoRYBBGCUE8DQboJBBAsFmF13g/IhCUDEL8AEUocCOAYpoYsZYrRkiiEEfkdhAw9G1AAGwiNaPH9PfQOGqJqGnxREhZEzAyHMLoBfVjKJz8nvP6j9gl86PkbRJwk8SLz4Y249xHhmIYO8TIXwOrWMEBHxxzjIR73MX3yxfwARAhBPc6EjY3FY7xeJ3xmmHX5g16E%2BfdZCSRNbO2fgnZuwMF7JIN1Q4RxZVSeH7eL75mmWGW0g8Kz90P7Ka0ipr/inv/WSM%2Bp3%2BTSky5SBEpgRkTav%2BPS0yfSYGWOf%2BFk8k9%2BcBUBSysySkyqayKBCB4BlImBT%2B8ImyjItkOyUuG8QUMCcue8kUCuR8ZyaUGU1%2BOUQ%2BpIN8HOb%2BHyg45QqAGQ2asgRYL04e94CAMC5Ok4JqewCQ0M/6qQ1UtUDU2qzqO6R4Ehu4t6HUshzQ8hMada2g6GcyHBmQyKaq2aqAVAVARgBAPyAhg4JQWApg/AmQJqr4mh6SVAEAuk6GDE4eLaUmO2xY4e6AmQsgsGdM8MjGOI3h06vhb21hgRwRPaoRVAEu7BmB%2B4do2g%2Bo4q%2BKL%2Bb4C0dEeRCqmmQBrEto2oGRYqWRIkoyP4QEhRL2ASmOEAyKJYLUbI5oHUXUJUnc3gTA/US8xBRS%2BhNaxIsgU0vO4aVq0h96KGo63o2ovoAOys0xjqr0oxL0y6Ex5aAuVayGjqj6Poz2YSgx6Bq4kRh67aFU1h0Kmg/AwAhICAVQDhaqph5hVqPafBC0oxOIR4LxFhHA4RWMpEZxEm7aeA/h%2BqNxdxBADxAgjhHgvxbxJqHxIx5Mnw74CJlhyRw0QJumURcklxlM4e1xtx9xjxcJGJsGyJCACg6oZhfxAJ2JykwJBAxhckYJVx6AkJpJsJzxdJiJhaVJaxcY6JfJmJbBw0NmhJg4LAvAi6c4EAyJjmCAZAxIxADJr2V2HBMpTAcpLACpwAM8h2r0eAC0eAWJr22mWpspBa8pipX2r0KpTY6pJM0W4JMpHAup%2BphpYOxpC0apmmy88%2BYM8anw5KaxlMGx16kx2xQuiahB9R2I4eQgNx4QDYZJvJrxka7xBpoZXx2IPxopHA3pJIDJSZBAKZ3AaZPJ8JoplJOZYZqJIpmZRZ02WJuym8FBhyVBxytBJ8Z8jBE4t%2B6uo8muBC2upAb8NgpAn8t%2BkeJugCpAwCFuuAVukCtuMCDujwzunuagbuWgHuBgRgPuuCDg34Ae7gQcJCIewQYeGKRqyA2pke5eseaQ9euQCeoguiEiAAnN%2BLIE0Pwm0G%2BV0P%2BT0K0F%2BUML%2BVHmMDIhosBY3ksDBUousBBdUFBU3pnk3qhSAL%2Be3sYl3uPj3hYoaKkIPrOSPvPq4vCLpCvkTj4sSH4qvpviOdvhjLvg2E2FEofsfvEufoklflcrfvedqZkhAcgfgaAYeEgXgYss/mMvoTJSAR%2BIARMgskpe0tJTkvAcJFJbAYpZ/nJPJScZARJTMipRgVpVgcJDgaspZaZYQRyAMWvKQTLp2WFPLofKcslPQZcjfneVQA%2BbwMOUcfoeHlwTwUSHweCbIIvu2OUCaliSeJoB4HUHyOUIQG5NFNgMWK8qiAAGLGBqrFibRoDvKfIeIcCE6YY8gAAq9454thmAsgKQjARIGK8QJAPyME%2BU1EPymEGYBAFKvIby5EHyXy9AlVXhuJ5xkMqsuqxog4cRIRcMSRmmzJrJSc/qC1S1CRK1iVPI4IYaoK5orUxk2yxx7B61UGxAVg7RUpxJ2Zouv60Zg6Oxr6exia00ehZsOJPhckt14JD1SJOZkZCGr1yxW6r0O65pxlHBf1E05QgNnJdZT18G/O4NG6Mxn1B4qJDammoV01IJ/1iNHJNxj1DFz1WxGNuxkNv4uNnhFcUM81HBgVOpNppgXpScf4t1qmTAR42IO6%2BNLpTM4JrNcpHNdpTMP4PNE0fNnwHgaIgtCZEpqsW1LN2p4tnNUMAEVg5QqmetOIStF222at4eYt7NWtqt0tBtN1BtCtRtDEgZq8HsB1R1zAaJjtTlP1TJhNLJ11mgd1C1QNApIN4xUZVNd6mNH1dahE31gJPt8N/4gdHBwdnNoN6NkdNNzqoyDNF1P%2BcNeJxImgJN91yN5N6dL1md71W6hE9Nzpl1vtG1/4JdQdZdwNqNfOldSG1d2d/4dd4p22zNZtGtFtktf4AdC0E9ht9dXNotI9xhEtOZTNP4U9i0ct9tMN3mp61h5tC9ltT0K9Ntxd/NnwDtjNqtc91pe9ktAEx9RddtitDJTtGGMOrtIK7t4UZ1Xt8dyqV17aHgydRJbdIdHdmxahAGPd2NeNU2BNidADSNZN7dFNaNXdED4GI6iaMyudicv1hdq2LdKdwDadYdYNVd6DQGMddE/dMDsNf9GkBDQDiDIDyDndEd3d5DWNdaMy1DIV7cc1l9bN19S9c1NRctq2ctAtM9TNAjmtY9ojG069j9A9wtptg4u9Wai9hpAEHgNtOjJ9Z9ed2tMjo9wjB9MyujD9BjA0fKL9LtWKbt5o5cRS51ODCdeDzwgDEJKNLDYDUxUdNdYBcdjJv9jdUGwEnjqdyJFdbDaDKqnDEAr0Jcm9%2BddDvcDDXj5dJDGd7DcT0dLqf0cY0DxttDoT2awE6TkTodlN4Db1HDeTiTPDQZfDItO989Gj%2B9f4Hje0Ejp9Uj/DrTV97TcjiTYjXT8tSjytJtxjQjWjP4zwNt8z%2BjfT29Up6j/Amjm1czCzljT9NjU1yZ3j0TNTsZdaGolI1wXNpZg4BzmT1T0hJzEAZzWYRUWjbZLlHZBy7l3ZNBXlyuA5zBwlQVrBLFD8Y5FgL8E5vuM5/lrNc5uuZuICWAK5ECNu0C9ucCTuiCygu5Gg6Cnu3uOCU5DgvC55QepCoeFCUu0gRuz5jCcewF2gvCieZwP5ugoFgFgijLWeDA2F35WiiF9CFedeHQuQXL5eRevLWicFIrjgUileLekFuhNw%2BFpihFve/esaM%2BmAwITijIarxFA%2BxANiVLDic%2BLii%2B1FOStFRSG%2BLsF2G%2BwSRBrFGG7F%2B%2B0SR%2BsSJ%2BZ%2BmAF%2B4Iu%2BRr/A04PAFKggjYAKLASoUISSKSTBVLolCldlsltEulYl%2BldSK05lXSalBlylmlzSplGlelibSlMBqbxbObiBRb%2BbSbGkmbJlNbiT3%2BabGyrYWy39JY7z5Bnzu8%2B8Pzx85yDBglbAwVTTDd4VtAvB/BUpMVsIcVCV4pJ4kwKYEbN4KgWVAUMFnVVVr9nwdVDVogTVLVyCG7HVxAXVsEDwHAfVpgA1Q1rypVo15V3y27ERpTs1LTUpO1The1a1b7m14JX7haiR%2B19j79J1ntxTDd8NN1ETRDUTWTqDtTuTAT0NQtUHhdv4sHTDxDdz2xENvdqHkzJT0HutCDhzCHMTSHDz00jTFcuDM1UNFTcHVTKDlH%2BHmDdNzz2DzTQ9ajbT6zHT0tYjMtkjaHs9AzgjQzpj3NwnijBj/sF9EnsjpjOtNtutSzYnRjSnJjszjH%2BtR4G9AZez/KoHjA7tq0X9kHKTf7a9ZHtzrHNT7HlDyaYn9HRNoyWH5HuH1NkDXDT6yTbnft7axddnSDRzfjWd2Nz0hTQTsDGHIXpNXnDnEXvnCTfdXHyT0j2nMzXNK9YjU9onNDW9vHazGzy9Hnk9cnmXinqz/HZXVtoyR9BthXVnWntXgzAnN9h9k9OzRniqtKh1YH8tEHSxbjDH4joXzD4XeH/jsxRTo3ITcDnn9nrDjns3HH83ztP9pxNnOjk3OHyXM3kXlDn0MXM9gXTde3iXK3vjR3qX3DGXyjxX0zUnhpf4ADCjGnRX4n7XknnX0n8j4cVXT3/72Xr3mz5jG0zXvTmnNXC1pX%2B92jFjBnEzF2z9A3DjnwTj1jVnF311Hj%2B38H3nZDyHsxSTrnY37n4ThPLHq3KXdTtN5PRH6H438zNPoD4da3x3%2BTtHedePZTbP13YXFHXPvnlUwEvPCnH78PdXgnIz3TX3rX/Tv3ynb3czozwPzPoPKvOnEP5Te00PVjzTqjCPXXiT2zKPRv2I6PxkZZ2HRPh3r1DzZzOIFzTNVzNzwvxPHUzvEEXHrz4p7ZXbd%2BXzvbnlSu/ZQ7LBRUW%2BoLT84LOuuCM5bAcLpu1wOoWgVgh48f2gtgLAtQ9ceeaI2gKeVge8KeKeNQzwDQk5euFgtgHAjgxu8Li5MAUAbfS5kkMCa50YXf9A1Q1ig4qV7wIgwAe8mgh4duKKjfEA5Qvu6VzAxA5K8CtgC/fA5KAA8uUHYDBSv6QKVWwMghv6fsv7glgC2MAKRbQLQI35i6QFgAWC4BoGf3gKSgkBirf1OZhGMAfnv%2BavH1OV7DlBiA6/dIFgF9x4R8%2Bd/DFMQC4JGBmQmAR/sADPygBTcigXgMAA4DRQ8AmAe8Bv2apvxty2LVBPuRdwEtfcDgf3KP0DyXk/AQAxvpAGuCoAYqrQW/nyA377Q%2BQAIW6BeR8DeBNAaIcsPOHxy3QqEMAowHyEHCbQ%2BQVALsJIM3ZNgGo5YWQagC4G0BZA8g09vVEwAfwYBTYLAAwIgCGIBWKwF8oIgWDMtxE3CbluYO5bYVdgJg5CnImAoODo8heeViy2sEYUXBteHRFXgkQKxlWneRwFrgT6Qsk%2BlgEsEayH58hzQI/G8HvCkBaxJoEAZFpjheC6FbA85UFsAiIAZBUWfATAZYD5AJA2A3rWwIUI4DGBAgtAFQAgFQD3ha%2B%2B/PvlUHISPBB%2BqVOIYQnlr1xkhtgTAOAhIDJIm%2BO5EgXi0PLYIKBXQFgBIAzCoA0hxAAABJXgvAT4BgOCFbCoB8BjAAYXvxmHMA0ACw7YYQLz6zC0AkwfACcPUSXDLADfAgJcOqGSBah9QxoXvzyG0B7I6AEANf2lJ8h5whIWEAwB1DG4SQxaL4YeHvAgDZAK/UIRCyaGfwLAPwlgH8O4CVRF8QIt0B0NiEWhuhiQ5IZVAWGxhhEZEbvkSKKhZD4W1wB4qWCGBGDSAGfAQXDFYQeBtACtGoKyPqA8IwWufcIVOQREN98E2QoBB33NwtCe%2BD7bviACxHxCx%2BzwCfooDoDT9KAc/XBGvyX5781Rm/bfrvzv4H9Wqx/ClL7nP6ZBL%2BwbW/s7gf6j9n%2BU5ElEhQ/6%2B5v%2ByAX/nf3/6%2B4gBIApfmAMeBTlIBe/GAXAMwAICkBKAlvniELBYCcBeAggXv1GF7lxhmCI8oS1sAOAFgpLWgQQmbCGCmBLApiMUI4HlhuBRoXgb4AEFCC5AmQUQeknEHw4pBugqoPoOojwBjBbg3IHS1fIysLBn5fwdYPZYrBbBvY8Ct2J2DQVBWReWweKw8FWDhx3gjsb4ObyeCrgQQkxEq3j5wioWkQrEV0NH49CkhcMAkYMMuJ7xMhzfNAbkO4K0AChxAIoRYBKF0glgpwCoVeKqE1C6hDQpoRKP75tDLAm4nEduLxFwx%2BhB44YQeWQQ4t3cZAxMVMIWD7C5hCw5YRwFWGMANhRAY4bsLv4wTDhB444XsLOE4p7hJQPfgCAIn19rhJQR4UsFfGvC7%2B7wz4d8NoC/D/h6I4EWGzBEgAIRUImEWCzXERDER9E5Ef8LRGAi%2BoUQlgDEK3EJDehe41IQeKJG6ASR/fIkQrApFp9SA1IrANUDpEMiU8UgPPFYG/J1AFadQbQM8CsCaAGgOfPPrUEPDwjbhMQQUS3zgCwBRRSIbvqiw/FDBpRhCcfpP0VFVAZ%2BKoqcpqI1ElB1%2BW/HfvED356ij%2BJ/I0ZgAv5X8b%2Be/S0U/29G2BbR4we0bgkdHOjncro3BO6NAGgIIBTYKAc7n9FNBAxiAq0UqFDEYCIxuA7CXf1jG4sQJXuSCSeSEQEJqBxYkhPQKbHTkcx50PMZwMLHMgep/GQQSiJEFGgxBfkmsR4DrHEAGxWYkcaYLbG2DLBqiBYAOIEQ%2BCdpPLIcfggnHCtS8rgpCu4JQqHSjgJ0w4HOPsF4VghgQ1cYnz5EbjohnQ38RJN3EpDCRLwJSSeIXJnj8hUCSocUNKH3jJAj4zAeROeFvjfc7k4gF%2BIsA/iZRO4voQUCAlfCFgzU8Cfi3alEtOpGE%2BYQePgmIT1hmw1CV8PQm4Sjh0Y6mQcLwk3C7%2BREt%2BHcIeEviXhVwmiV8KREoiARmQIEaQEhFMBoRmLWES9Lr68yBJEAJiZiPenYjUZ/4n6TJL%2BlHh0IpIl4CXGUmAIqRAKdSZQHT77kpA%2Bk7QL%2BW/Ip5ngcotEDUA8BWAnAlgHkTZJImN8FgQo1vvAE74uT%2B%2BbksUVKPlkyjvJCo8nH5OVHz8Qp6ou/pqLCk6jncUUggAaNP42i4pJohKeaLSlVSUpRo1/naMbFZTTAP/NsH/zDQADbABUz0UVNwS%2BjoBVQAMUGOqkuBap4Y7AQ1LplEDQJYw1qeQI6lOBupZLPqYwIGkrA2B%2BYrgfcJ4FB5SxU0isTNKrFzTJBC06cnoOSSNiB5tLJhD4M2nJ5tpAFPsXtJ3mDiFW04xwRdOcGzjjpfgw%2BUdOlanS7pV0h6SYhebPTeRdfESWJM%2BlFglZ%2B41cmSMuDaychSAd4ZeOvG3iyhD40gJUJhmUT3xYopGSjNxGSSv%2BmMroDjNIF4zJh3c0gETLgkrC1hyErYQQLQnO4sFWE1uacIZkXDiJzuFmbZJZmQLOZbw88bRKlmVkhJQsjiWLK4kSzpylgZheaBllCS5Zokj6YrIQVfyIEZItWWKNkm/yAZD8XWTSI0mGyeEOkuoJXxZF1As%2Bv5O2eggsnPzuFzs%2ByaeJFEgIvZVQH2aYoH7%2ByvJconycHLPahzVR4c0/s7ijnaiIpuo%2BUIf3jkxSz%2Byc00dfzTn38M5yA1Kff2zkZTc5X/fOU6MLkuji5bo5sB6PJRejipdIP0TXIql1yn%2BNUtAWGMwHNyoxjAGMcQLjGdz8ZyY2oF1IbnjSMx5QFacwKHnDSCxY8osRPMmnCDp5zIWaWe3mlCDb8mgiBGlUIAcBboyVOoItOWn9S159LWcZvICE2C95YFbPJfLOmjjr5t08%2BfOKnFXybp8wW%2BSsvvnsAS4nCvRQiNfnCL4F30sRekL3hazZFCLQBSDKfFgy7x5Q8BU%2BLoVwzcECM2BfLPEkfyEFgE1csMO/AoL4xbU9BQTN4TELVypM3BRTIIVUyiFNMkhUUvplzCKFVw6hc7PwkMBPlVE53NzLokMSWFAs4EcLNFkIJxZpynhXxL5mCSyVgit%2BSIquXSTv5msyRRYqJEGI/5/YVSXrNpFKK0QUgFKinm/JogPAlfG2XUGL5WAzyDsrhfyLsmuyHJxihGeYtkCSjPJo/QOVPxDmz8w5i/ZxavycXRz3FsczxfqJ8VJz4pZopKcEutFpTwl7/SJf0OiU5TbAeUwAYksKngDK5JU9JbAMyUOqclC5PJfVMKVXCwVZSyFRUrTxpi%2BBdAzMf1IaWsCmlo83MK0toGTyOllY1ANWPnm%2BAqWEy5eStOmXtib5cynsfvN2mzj9p9g1aU4OLxnzj5QrC%2BQuJ2Wnyb5WFO%2BUuPYAGITlTs85QrMuX4i2V4il4DyvuWLkAF54oBWwNzUzz81c8qQUIL3zEBboRatgOWHBlvKIFHMr5VOR%2BUYs4Ff4wFRjOBVfDeE0aiCbGrwRp4YVECOFUhIRU7CkVZC2CaiquFEzMVhE3FTQtxX4quZjCnmXSsYmsKWJww9iSLM4lPynZvChlRiOHX/K0ZUk36XvF4TySqgRIlPDIqFHyL9ZmkrQHUB0kl9LZaIZ4BKrtmK0LZ3IxVTQsMU6ywWC8/PiXykDGSPAVfcVRbNYQp58gTs3laEOeD0aSJ%2BG0gOIJjzaAgAA%3D%3D%3D)

Consider compilation target: AArch64 / Armv8-A.  

Consider uarchitecture model Arm Neoverse V2.

Consider compiler: Clang 23.1 (most recent available) and `-O3` optimization level, unless specified otherwise.

The present goal is to provide a genuine benchmark of the MRC implementation over the ARM uarchitecture extensions. Focus in particular on the SIMD, NEON, SVE models.

For benchmarking purpose, consider LLVM-MCA after isolation of the relevant piece of code. Based on that, produce some top level metrics for benchmarking purpose:
- Cycles per processed sample 
- Pipeline Usage Efficiency (PUE)
- Execution Density (ED)

## Kernel

For each complex input sample:
$$
y[k] = \sum_{a=0}^{3} \mathrm{conj}(h_a[k]) \cdot r_a[k]
$$

This is typical usecase for LTE-A MIMO receiver. This operation is performed for each RE, that could be (20MHz, FDD Transmission Scheme), 14 OFDM symbols, 1200 subcarriers per subframe (1ms), thus 16,800 MRC per ms, ~17e6 MRC per second. Definitely a candidate for massively repeated execution on a DSP.

## Methodology

To make LLVM-MCA results comparable, each benchmark processes exactly 4 complex output samples.

LLVM-MCA regions isolate the kernel:

```cpp
asm volatile("# LLVM-MCA-BEGIN mrc4_block");

// kernel

asm volatile("# LLVM-MCA-END mrc4_block");
```

Two initial builds are compared:

Naive Implementation aka Scalar
```text
-O3 -std=c++17 -mcpu=neoverse-v2 -fno-vectorize -fno-slp-vectorize 
```

SIMD (automatically enabled by compiler)
```text
-O3 -std=c++17 -mcpu=neoverse-v2
```

A first attempt was made leaving the complete variable-size MRC loop. However, the compiler-generated code contained both a vectorized main loop and a scalar remainder loop. Then LLVM-MCA analyzed both paths as part of the same code region. This made direct comparison misleading: the reported instruction count, total cycles and block throughput did not represent the same amount of useful work between the scalar and SIMD implementations. The benchmark was therefore reduced to a fixed block of 4 complex samples to match the width of a 128-bit NEON vector (`4 × float32`).

## Top-level Results

Performance outcome
| Metric | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v4.1 SVE FCMLA | v5 SME* |
|---|---:|---:|---:|---:|---:|---:|
| Instructions / MCA region | 134 | 75 | 26 | 45 | 29 | 37 |
| µOps / MCA region | 170 | 93 | 55 | 123 | 47 | 39 |
| Block RThroughput | 28.3 cycles | 16.0 cycles | 9.2 cycles | 20.5 cycles | 7.8 cycles | 6.5 cycles |
| Cycles / sample | 7.08 | 4.00 | 2.30 | 5.13 | 1.95 | N/A* |
| Speedup vs Scalar | 1.00× | 1.77× | 3.08× | 1.38× | 3.63× | N/A* |

\* v5 uses a hypothetical Neoverse V2 + SME LLVM-MCA configuration.
The Streaming Vector Length is not established as 128 bits by this experiment, so the MCA region cannot be normalized to exactly four complex samples.
The reported 6.5-cycle Block RThroughput is therefore retained as a raw LLVM-MCA result only.

TODO: Provide script for PUE, ED, based on log

### Top-Level Observation / Discussion
SME does not help

TBD

## Going More into the Details (Inside the Pipeline)

LLVM-MCA timeline helps in going beyond the above averaged metrics. See v*.log and consider notations:
```text
`D`  Dispatch
`=`  Wait before Execution
`e`  Execution Slot
`E`  Execution Completion
`-`  Wait before Retirement
`R`  Retired
```
Let me build some timeline metrics to produce some custom descriptive values derived from the LLVM-MCA timeline iteration.

Pipeline outcome
| Timeline metric | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v4.1 SVE FCMLA | v5 SME* |
|---|---:|---:|---:|---:|---:|---:|
| `e` | 492 | 206 | 134 | 228 | 137 | 188 |
| `=` | 562 | 443 | 187 | 156 | 156 | 212 |
| `-` | 482 | 225 | 45 | 107 | 65 | 109 |
| `= / (= + e)` | 53.3% | 68.3% | 58.3% | 40.6% | 53.2% | 53.0% |

### Pipeline comparison: Scalar (v1) vs Auto-SIMD (v2)

Interestingly, the auto-vectorized implementation is much faster overall, but shows a higher proportion of pre-execution waiting. That suggests some optimization question.

Highlight some LLVM-MCA timeline for discussion.

#### 1. Loads: same latency, more data

```asm
Scalar                           Auto-SIMD

DeeeeeeER  ldp s1, s2, [x0]      DeeeeeeER  ldp q3, q4, [x0]
```

Yet same execution latency (6 cycles), v2 deals with 128-bit vector registers and therefore moves more data per instruction. Thus increase in parallelism with no significant penalty in instruction latency.

#### 2. Scalar dependency chains

Typical sequence v1:

```asm
D====eeeE...       fmul   s25, s2, s18
D======eeeeE...    fmadd  s25, s17, s1, s25
...
D========eeE...    fadd   s25, s25, s0
D==========eeE...  fadd   s2, s25, s2
```

`=` cycles increases and shows instructions being dispatched but waiting before execution. Successive MAC and ADD operations introduce dependency and clip parallelism.

#### 3. SIMD computation introduces data rearrangement

v2 processes 4 `FLP32` with 1 instruction, 4 bytes each so 16 bytes (128 bits):

```asm
D=====eeE...          trn2  v2.4s, v0.4s, v0.4s
D======eeE...         trn1  v0.4s, v0.4s, v0.4s
...
D===========eeeE...   fmul  v1.4s, ...
D===========eeeeE...  fmla  v1.4s, ...
```

The `.4s` vector operations perform 4 FLP operations in a single operation (parallel), excellent. But see `trn2` / `trn1` that rearrange the interleaved real and imaginary components, this is a penalty induced by SIMD when dealing with `struct Complex { float re;  float im; };`. In memory the array of data is then interleaved `re0 im0 | re1 im1 | ...` and the compiler thinks it is mandatory de-interleave. Well, this could be handled differently to save this cost by preparing the data with proper layout or considering `re` and `im` are independent so their order does not matter. This later aspect is a special case and does not scale up.

#### 4. SIMD does not eliminate dependency chains

Towards the end of V2:

```asm
D============eeeeE-R     fmla  v1.4s, ...
D================eeER    fadd  v0.4s, v0.4s, v1.4s
...
D===========eeeeE--R     fmla  v1.4s, ...
D=================eeER   fadd  v0.4s, v0.4s, v1.4s
D====================eeER stp  q2, q0, [x8]
```

The auto-vectorized implementation performs substantially more useful work per instruction, but long pre-execution waits remain visible.

The final accumulation and store are still constrained by preceding results.

#### 5. TBD

TBD

### Scalar to SME

#### 1. Architecture outcome

| | v1 Scalar | v2 Auto-SIMD | v3 NEON | v4 SVE | v4.1 SVE FCMLA | v5 SME* |
|---|---|---|---|---|---|---|
| Data parallelism | 1 × FP32 | 4 × FP32 | 4 × FP32 | 4 × FP32 SVE | SVE complex pairs | Streaming SVE complex pairs |
| Arithmetic | Scalar FP | Vector FP | NEON FMA | SVE FMA | SVE `FCMLA` | Streaming `FCMLA` |
| Data access | Scalar loads | Vector loads | `ld2` / `st2` | Gather / scatter | Contiguous vector loads | Streaming vector loads |
| Data rearrangement | Minimal | `trn1` / `trn2` | Structured load/store | Gather / scatter | Native interleaved complex representation | Native interleaved complex representation |
| Main limitation | Scalar execution | Shuffle overhead | FMA dependency chains | Gather/scatter overhead | FCMLA dependency chains | Model / SVL comparability |
| Block RThroughput | 28.3 | 16.0 | 9.2 | 20.5 | 7.8 | 6.5* |
| Cycles / sample | 7.08 | 4.00 | 2.30 | 5.13 | 1.95 | N/A* |
| Relative speedup | 1.00× | 1.77× | 3.08× | 1.38× | 3.63× | N/A* |

\* SME is modeled by enabling SME on the Neoverse V2 LLVM-MCA scheduling model. Since Neoverse V2 does not implement SME, then v5 is a tentative ISA modeling experiment. Direct comparison in the benchmark is slightly speculative.

#### 2. Milestones

v1:   many scalar operations and dependency chains.

v2:   parallel computation and fewer instructions, but data rearrangement and remaining dependencies.

v3:   explicit NEON removes data rearrangement overhead. Some dependencies remain.

v4:   SVE vectorization, but gather/scatter overhead makes the naive mapping inefficient.

v4.1: complex-aware SVE with FCMLA removes gather/scatter overhead and reduces dependency pressure.

v5:   SME streaming further reduces modeled throughput, but the result is not directly comparable due to streaming vector length and the hypothetical V2+SME model.