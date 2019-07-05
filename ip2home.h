#pragma once
#include <WinSock2.h>
#include <stdio.h>
#include "util.h"
#include "utfencode.h"

char form[] = "POST / HTTP/1.1\r\n"
"Host: mylocation.co.kr\r\n"
"Connection: keep-alive\r\n"
"Content-Length: %d\r\n"
"Cache-Control: max-age=0\r\n"
"Origin: http://mylocation.co.kr\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36\r\n"
"Accept : text/html, application/xhtml+xml, application/xml;q=0.9, image/webp, image/apng,*/*;q=0.8\r\n"
"Referer: http://mylocation.co.kr/\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
"Cookie: popup=true; ASP.NET_SessionId=dsedcpj3wgbmpyyimftp44hx\r\n"
"\r\n"
"%s%s";

char view_state[] = "__VIEWSTATE=%2FwEPDwUJMjcyMDExNjYxDxYGHgJ4MQUSMTI2Ljk0MTU0ODkyMTM4MTEzHgJ5MQURMzcuNDc5MTQ1MjgzMTQ3NjMeCWFkZHJJdGVtczL%2BAgABAAAA%2F%2F%2F%2F%2FwEAAAAAAAAADAIAAAA%2FQXBwX0NvZGUsIFZlcnNpb249MC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj1udWxsBQEAAAAOSXRlbUNvbGxlY3RvbnMBAAAAE0NvbGxlY3Rpb25CYXNlK2xpc3QDHFN5c3RlbS5Db2xsZWN0aW9ucy5BcnJheUxpc3QCAAAACQMAAAAEAwAAABxTeXN0ZW0uQ29sbGVjdGlvbnMuQXJyYXlMaXN0AwAAAAZfaXRlbXMFX3NpemUIX3ZlcnNpb24FAAAICAkEAAAAAQAAAAEAAAAQBAAAAAQAAAAJBQAAAA0DBQUAAAAKUnNzQ2hhbm5lbAQAAAAHYWRkcmVzcwF4AXkHZXF1bG51bQEBAQAIAgAAAAYGAAAAI%2ByEnOyauO2KueuzhOyLnCDqtIDslYXqtawg7LKt66Oh64%2BZBgcAAAAGMzA2NTgxBggAAAAGNTQyNDE0AAAAAAsWAgIDD2QWJAIBD2QWAgIED2QWAmYPZBYCAgEPDxYCHgRUZXh0BT7rqZTsnbgg7ZmU66m0IOyijOy4oe2VmOuLqOyXkOyEnCDsnqzrk7HroZ3snbQg6rCA64ql7ZWp64uI64ukLmRkAgUPDxYCHwMFDTIxMS40NC4xOTYuMjdkZAIJDw8WBB4ISW1hZ2VVcmwFBzAxMS5wbmceB1Rvb2xUaXAFBuunkeydjGRkAgsPDxYEHwQFBzAxMC5wbmcfBQUG66eR7J2MZGQCDQ8PFgIfAwUPfjPsi5wgLTEyLjAg4oSDZGQCDw8PFgIfAwUPfjbsi5wgLTEyLjAg4oSDZGQCEQ8PFgIeC05hdmlnYXRlVXJsBUlodHRwOi8vd3d3LndlYXRoZXIuZ28ua3Ivd2VhdGhlci9mb3JlY2FzdC9kaWdpdGFsX2ZvcmVjYXN0LmpzcD94PTU5Jnk9MTI1ZGQCFQ8PZBYCHglvbmtleWRvd24FpAFpZihldmVudC53aGljaCB8fCBldmVudC5rZXlDb2RlKXtpZiAoKGV2ZW50LndoaWNoID09IDEzKSB8fCAoZXZlbnQua2V5Q29kZSA9PSAxMykpIHtkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgnYnRuQWRkcjInKS5jbGljaygpO3JldHVybiBmYWxzZTt9fSBlbHNlIHtyZXR1cm4gdHJ1ZX07IGQCGw8PFgIfAwUj7ISc7Jq47Yq567OE7IucIOq0gOyVheq1rCDssq3ro6Hrj5lkZAIdDxAPFgQeDkRhdGFWYWx1ZUZpZWxkBQdBZGRyZXNzHgtfIURhdGFCb3VuZGdkEBUBI%2ByEnOyauO2KueuzhOyLnCDqtIDslYXqtawg7LKt66Oh64%2BZFQEj7ISc7Jq47Yq567OE7IucIOq0gOyVheq1rCDssq3ro6Hrj5kUKwMBZxYBZmQCJw8PFgQeCUJhY2tDb2xvcgkOrz7%2FHgRfIVNCAghkZAIpDw8WBB8KCfDw8P8fCwIIZGQCKw8PFgIfBgV%2FaHR0cDovL21hcC5uYXZlci5jb20vP2RsZXZlbD0xMyZsYXQ9MzcuNDc5MTQ1MjgzMTQ3NjMmbG5nPTEyNi45NDE1NDg5MjEzODExMyZzZWFyY2hDb29yZD0xMjYuOTQxNTQ4OTIxMzgxMTMlM0IzNy40NzkxNDUyODMxNDc2M2RkAi0PDxYCHwYFWmh0dHA6Ly9tYXAuZGF1bS5uZXQvP21hcF90eXBlPVRZUEVfTUFQJm1hcF90ZXJyYWluPW9mZiZ1cmxYPTQ4NzA3NSZ1cmxZPTExMDU0NzgmdXJsTGV2ZWw9MmRkAi8PDxYCHwYFUWh0dHBzOi8vbWFwcy5nb29nbGUuY28ua3IvP2hsPWtvJmxsPTM3LjQ3OTE0NTI4MzE0NzYzLDEyNi45NDE1NDg5MjEzODExMyZ0PW0mej0xOGRkAjMPDxYCHgdWaXNpYmxlaGQWAgIBDw8WAh8DBZAqKklTUCDsl4XssrTroZwg67aA7YSwIO2VoOuLueuQnCBJUOuKlCDsgqzsmqnsnpDqsIAg7J6F66Cl7ZWcIOuNsOydtO2EsOulvCDquLDrsJjsnLzroZwg7JyE7LmY6rCAIO2RnOyLnOuQqeuLiOuLpC4qDQotLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLQ0KMjAxOC0xMC0wNyAxMzozMjo0OC41NDMJCTIxMS40NC4qLioJ7ISc7Jq47Yq567OE7IucIOq0gOyVheq1rCDssq3ro6Hrj5kgWzHsoJBdDQotLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLQ0KDQoq7KeA64%2BE7IOB7JeQIO2RnOyLnOuQmOuKlCDsnITsuZjripQg64uk7J2M7J2YIOyasOyEoOyInOychOulvCDrlLDrpoXri4jri6QuDQooSVDqsIAg64%2BZ7J287ZWcIOqyveyasCDspJHrs7Xrk7HroZ3snbQg67aI6rCA64ql7ZWp64uI64ukLikNCg0KMS7rj5nsnbwgSVDrjIDsl63sl5Ag6rCA7J6lIOunjuydtCDrk7HroZ3rkJwg7JyE7LmYDQoyLuuTseuhneuQnCDsnITsuZjqsIAg64%2BZ7J287ZWgIOqyveyasCDstZzqt7wg65Ox66Gd65CcIOychOy5mA0KMy7stZzsooUg65Ox66Gd7J287J20IDHrhYQg6rK96rO8IOyLnCDsnITsuZgg7J6sIO2ZleyduA0KNC7sl7Drj5nsl5Ag7J2Y7ZWcIOyasOyEoCDrsI8g64%2BZ7J287JyE7LmYIOuTseuhnSDsi5wg6rCA7IKwIOuTsQ0KDQoNCg0KKldIT0lTIOyhsO2ajOqysOqzvCA9PT4gcXVlcnkgOiAyMTEuNDQuMTk2LjI3CgoKIyBLT1JFQU4oVVRGOCkKCuyhsO2ajO2VmOyLoCBJUHY07KO87IaM64qUIO2VnOq1reyduO2EsOuEt%2BynhO2dpeybkOycvOuhnOu2gO2EsCDslYTrnpjsnZgg6rSA66as64yA7ZaJ7J6Q7JeQ6rKMIO2VoOuLueuQmOyXiOycvOupsCwg7ZWg64u5IOygleuztOuKlCDri6TsnYzqs7wg6rCZ7Iq164uI64ukLgoKWyDrhKTtirjsm4ztgawg7ZWg64u5IOygleuztCBdCklQdjTso7zshowgICAgICAgICAgIDogMjExLjQ0LjEyOC4wIC0gMjExLjQ0LjI1NS4yNTUgKC8xNykK6riw6rSA66qFICAgICAgICAgICAgIDog7JeQ7Iqk7LyA7J2067iM66Gc65Oc67C065Oc7KO87Iud7ZqM7IKsCuyEnOu5hOyKpOuqhSAgICAgICAgICAgOiBicm9hZE5uZXQK7KO87IaMICAgICAgICAgICAgICAgOiDshJzsmrjtirnrs4Tsi5wg7KSR6rWsIO2HtOqzhOuhnCAyNArsmrDtjrjrsojtmLggICAgICAgICAgIDogMDQ2MzcK7ZWg64u57J287J6QICAgICAgICAgICA6IDIwMDAwMTI2CgrsnbTrpoQgICAgICAgICAgICAgICA6IElQ7KO87IaMIOuLtOuLueyekArsoITtmZTrsojtmLggICAgICAgICAgIDogKzgyLTItMTA2LTIK7KCE7J6Q7Jqw7Y64ICAgICAgICAgICA6IGlwLWFkbUBza2Jyb2FkYmFuZC5jb20KCuyhsO2ajO2VmOyLoCBJUHY07KO87IaM64qUIOychOydmCDqtIDrpqzrjIDtlonsnpDroZzrtoDthLAg7JWE656Y7J2YIOyCrOyaqeyekOyXkOqyjCDtlaDri7nrkJjsl4jsnLzrqbAsIO2VoOuLuSDsoJXrs7TripQg64uk7J2M6rO8IOqwmeyKteuLiOuLpC4KLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0KCgpbIOuEpO2KuOybjO2BrCDtlaDri7kg7KCV67O0IF0KSVB2NOyjvOyGjCAgICAgICAgICAgOiAyMTEuNDQuMTk2LjAgLSAyMTEuNDQuMTk2LjI1NSAoLzI0KQrquLDqtIDrqoUgICAgICAgICAgICAgOiDsl5DsiqTsvIDsnbTruIzroZzrk5zrsLTrk5zso7zsi53tmozsgqwK64Sk7Yq47JuM7YGsIOq1rOu2hCAgICAgIDogQ1VTVE9NRVIK7KO87IaMICAgICAgICAgICAgICAgOiDshJzsmrjtirnrs4Tsi5wg7KSR6rWsIO2HtOqzhOuhnArsmrDtjrjrsojtmLggICAgICAgICAgIDogMDQ2MzcK7ZWg64u564K07JetIOuTseuhneydvCAgICA6IDIwMTQwMjE0CgrsnbTrpoQgICAgICAgICAgICAgICA6IElQ7KO87IaMIOuLtOuLueyekArsoITtmZTrsojtmLggICAgICAgICAgIDogKzgyLTItMTA2LTIK7KCE7J6Q7Jqw7Y64ICAgICAgICAgICA6IGlwLWFkbUBza2Jyb2FkYmFuZC5jb20KCgojIEVOR0xJU0gKCktSTklDIGlzIG5vdCBhbiBJU1AgYnV0IGEgTmF0aW9uYWwgSW50ZXJuZXQgUmVnaXN0cnkgc2ltaWxhciB0byBBUE5JQy4KClsgTmV0d29yayBJbmZvcm1hdGlvbiBdCklQdjQgQWRkcmVzcyAgICAgICA6IDIxMS40NC4xMjguMCAtIDIxMS40NC4yNTUuMjU1ICgvMTcpCk9yZ2FuaXphdGlvbiBOYW1lICA6IFNLIEJyb2FkYmFuZCBDbyBMdGQKU2VydmljZSBOYW1lICAgICAgIDogYnJvYWRObmV0CkFkZHJlc3MgICAgICAgICAgICA6IFNlb3VsIEp1bmctZ3UgVG9lZ3llLXJvIDI0ClppcCBDb2RlICAgICAgICAgICA6IDA0NjM3ClJlZ2lzdHJhdGlvbiBEYXRlICA6IDIwMDAwMTI2CgpOYW1lICAgICAgICAgICAgICAgOiBJUCBNYW5hZ2VyClBob25lICAgICAgICAgICAgICA6ICs4Mi0yLTEwNi0yCkUtTWFpbCAgICAgICAgICAgICA6IGlwLWFkbUBza2Jyb2FkYmFuZC5jb20KCi0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tCgpNb3JlIHNwZWNpZmljIGFzc2lnbm1lbnQgaW5mb3JtYXRpb24gaXMgYXMgZm9sbG93cy4KClsgTmV0d29yayBJbmZvcm1hdGlvbiBdCklQdjQgQWRkcmVzcyAgICAgICA6IDIxMS40NC4xOTYuMCAtIDIxMS40NC4xOTYuMjU1ICgvMjQpCk9yZ2FuaXphdGlvbiBOYW1lICA6IFNLIEJyb2FkYmFuZCBDbyBMdGQKTmV0d29yayBUeXBlICAgICAgIDogQ1VTVE9NRVIKQWRkcmVzcyAgICAgICAgICAgIDogU2VvdWwgSnVuZy1ndSBUb2VneWUtcm8KWmlwIENvZGUgICAgICAgICAgIDogMDQ2MzcKUmVnaXN0cmF0aW9uIERhdGUgIDogMjAxNDAyMTQKCk5hbWUgICAgICAgICAgICAgICA6IElQIE1hbmFnZXIKUGhvbmUgICAgICAgICAgICAgIDogKzgyLTItMTA2LTIKRS1NYWlsICAgICAgICAgICAgIDogaXAtYWRtQHNrYnJvYWRiYW5kLmNvbQoKCgotIEtJU0EvS1JOSUMgV0hPSVMgU2VydmljZSAtCgpBTihVVEY4KQoK7KGw7ZqM7ZWY7IugIElQdjTso7zshozripQg7ZWc6rWt7J247YSw64S37KeE7Z2l7JuQ7Jy866Gc67aA7YSwIOyVhOuemOydmCDqtIDrpqzrjIDtlonsnpDsl5Dqsowg7ZWg64u565CY7JeI7Jy866mwLCDtlaDri7kg7KCV67O064qUIOuLpOydjOqzvCDqsJnsirXri4jri6QuCgpbIOuEpO2KuOybjO2BrCDtlaDri7kg7KCV67O0IF0KSVB2NOyjvOyGjCAgICAgICAgICAgOiAyMTEuNDQuMTI4LjAgLSAyMTEuNDQuMjU1LjI1NSAoLzE3KQrquLDqtIDrqoUgICAgICAgICAgICAgOiDsl5DsiqTsvIDsnbTruIzroZzrk5zrsLTrk5zso7zsi53tmozsgqwK7ISc67mE7Iqk66qFICAgICAgICAgICA6IGJyb2FkTm5ldArso7zshowgICAgICAgICAgICAgICA6IOyEnOyauO2KueuzhOyLnCDspJHqtawg7Ye06rOE66GcIDI0CuyasO2OuOuyiO2YuCAgICAgICAgICAgOiAwNDYzNwrtlaDri7nsnbzsnpAgICAgICAgICAgIDogMjAwMDAxMjYKCuydtOumhCAgICAgICAgICAgICAgIDogSVDso7zshowg64u064u57J6QCuyghO2ZlOuyiO2YuCAgICAgICAgICAgOiArODItMi0xMDYtMgrsoITsnpDsmrDtjrggICAgICAgICAgIDogaXAtYWRtQHNrYnJvYWRiYW5kLmNvbQoK7KGw7ZqM7ZWY7IugIElQdjTso7zshozripQg7JyE7J2YIOq0gOumrOuMgO2WieyekOuhnOu2gO2EsCDslYTrnpjsnZgg7IKs7Jqp7J6Q7JeQ6rKMIO2VoOuLueuQmOyXiOycvOupsCwg7ZWg64u5IOygleuztOuKlCDri6TsnYzqs7wg6rCZ7Iq164uI64ukLgotLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLQoKClsg64Sk7Yq47JuM7YGsIO2VoOuLuSDsoJXrs7QgXQpJUHY07KO87IaMICAgICAgICAgICA6IDIxMS40NC4xOTYuMCAtIDIxMS40NC4xOTYuMjU1ICgvMjQpCuq4sOq0gOuqhSAgICAgICAgICAgICA6IOyXkOyKpOy8gOydtOu4jOuhnOuTnOuwtOuTnOyjvOyLne2ajOyCrArrhKTtirjsm4ztgawg6rWs67aEICAgICAgOiBDVVNUT01FUgrso7zshowgICAgICAgICAgICAgICA6IOyEnOyauO2KueuzhOyLnCDspJHqtawg7Ye06rOE66GcCuyasO2OuOuyiO2YuCAgICAgICAgICAgOiAwNDYzNwrtlaDri7nrgrTsl60g65Ox66Gd7J28ICAgIDogMjAxNDAyMTQKCuydtOumhCAgICAgICAgICAgICAgIDogSVDso7zshowg64u064u57J6QCuyghO2ZlOuyiO2YuCAgICAgICAgICAgOiArODItMi0xMDYtMgrsoITsnpDsmrDtjrggICAgICAgICAgIDogaXAtYWRtQHNrYnJvYWRiYW5kLmNvbQoKCiMgRU5HTElTSAoKS1JOSUMgaXMgbm90IGFuIElTUCBidXQgYSBOYXRpb25hbCBJbnRlcm5ldCBSZWdpc3RyeSBzaW1pbGFyIHRvIEFQTklDLgoKWyBOZXR3b3JrIEluZm9ybWF0aW9uIF0KSVB2NCBBZGRyZXNzICAgICAgIDogMjExLjQ0LjEyOC4wIC0gMjExLjQ0LjI1NS4yNTUgKC8xNykKT3JnYW5pemF0aW9uIE5hbWUgIDogU0sgQnJvYWRiYW5kIENvIEx0ZApTZXJ2aWNlIE5hbWUgICAgICAgOiBicm9hZE5uZXQKQWRkcmVzcyAgICAgICAgICAgIDogU2VvdWwgSnVuZy1ndSBUb2VneWUtcm8gMjQKWmlwIENvZGUgICAgICAgICAgIDogMDQ2MzcKUmVnaXN0cmF0aW9uIERhdGUgIDogMjAwMDAxMjYKCk5hbWUgICAgICAgICAgICAgICA6IElQIE1hbmFnZXIKUGhvbmUgICAgICAgICAgICAgIDogKzgyLTItMTA2LTIKRS1NYWlsICAgICAgICAgICAgIDogaXAtYWRtQHNrYnJvYWRiYW5kLmNvbQoKLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0KCk1vcmUgc3BlY2lmaWMgYXNzaWdubWVudCBpbmZvcm1hdGlvbiBpcyBhcyBmb2xsb3dzLgoKWyBOZXR3b3JrIEluZm9ybWF0aW9uIF0KSVB2NCBBZGRyZXNzICAgICAgIDogMjExLjQ0LjE5Ni4wIC0gMjExLjQ0LjE5Ni4yNTUgKC8yNCkKT3JnYW5pemF0aW9uIE5hbWUgIDogU0sgQnJvYWRiYW5kIENvIEx0ZApOZXR3b3JrIFR5cGUgICAgICAgOiBDVVNUT01FUgpBZGRyZXNzICAgICAgICAgICAgOiBTZW91bCBKdW5nLWd1IFRvZWd5ZS1ybwpaaXAgQ29kZSAgICAgICAgICAgOiAwNDYzNwpSZWdpc3RyYXRpb24gRGF0ZSAgOiAyMDE0MDIxNAoKTmFtZSAgICAgICAgICAgICAgIDogSVAgTWFuYWdlcgpQaG9uZSAgICAgICAgICAgICAgOiArODItMi0xMDYtMgpFLU1haWwgICAgICAgICAgICAgOiBpcC1hZG1Ac2ticm9hZGJhbmQuY29tCgoKCmRkAjcPDxYCHwMFUu2YhOyerCDstJ0gMTA3LDQwMiDqsJzsnZgg7IKs7Jqp7J6QIOychOy5mCDrjbDsnbTthLDqsIAg65Ox66Gd65CY7JeI7Iq164uI64ukLlsyOV1kZAI5Dw8WAh8DBRk3NSAvIDIsNDg2LDc4NCAob25saW5lOjEpZGQYAQUeX19Db250cm9sc1JlcXVpcmVQb3N0QmFja0tleV9fFgIFB2J0blNhdmUFCGJ0bkFkZHIyZGlh21jNAmgtHjdxyt4gGiBHcMtLW%2Fp5DbG6eyV0U6I%3D&__VIEWSTATEGENERATOR=CA0B0334&__EVENTVALIDATION=%2FwEdAAbV8OdlHyfWcaTwrwcf3wVAlliAPKY%2BKvRmniYVjNuQiLZUdqXEqUEGZ4VhEwb0n5WjxkxrFmP1R0wBHRLR3IS5wpKQlsO%2BkYZ5j5xgi9pmWOYRQv8uufx%2F0wctsRSxXnq3SlVdZvycFRc6FwyxkKNPk999QVW9flWG9PetByHRTA%3D%3D&";

char elements[] =
"lbJuso=&"
"txtAddr=&%s"
"btnAddr2.x=22&"
"btnAddr2.y=11";

int Get_HomeAddr(char *data, size_t data_size, _Out_ char* homeaddr, size_t home_len) {

	char target[] = "<span id=\"IbAddr\" ImageAlign=\"AbsMiddle\">";
	char *pin;
	size_t homeaddr_len;

	pin = memstr(data, target, data_size);
	if (pin == NULL) return -1;

	pin += strlen(target);

	for (int i = 0; i < 512; i++) {
		char ch = *(pin + i);
		if (ch == '<') {
			homeaddr_len = i;
			break;
		}
	}

	memcpy_s(homeaddr, home_len, pin, homeaddr_len);
	return 0;
}
int sendall(SOCKET s, char* data, size_t len) {

	int tx = 0;
	while (1) {
		tx += send(s, data + tx, len - tx, NULL);
		if (tx >= len) return tx;
	}
}

int httprecvall(SOCKET s, char* buf, size_t bufsize) {

	char contentlen[] = "Content-Length";
	char num[128] = { 0, };
	char* pin;

	int datasize;
	int rx;

	rx = recv(s, buf, bufsize, NULL);
	pin = (char*)memstr(buf, contentlen, rx); //find tot len
	pin += strlen(contentlen) + 1;

	for (int i = 0; i < 128; i++) { // parse len
		if (*(pin + 1) >= 0x30 && *(pin + 1) < 0x3a) {
			num[i] = *(pin + i);
		}
		else {
			break; // end parse 
		}
	}

	datasize = atoi(num); // get tot data size

	while (1) {
		if (rx >= datasize) break;
		if (rx >= bufsize) break;
		rx += recv(s, buf + rx, bufsize - rx, NULL);
	}

	return rx;
}

IN_ADDR Get_Location_Server() {

	HOSTENT* h;
	IN_ADDR server;

	h = gethostbyname("mylocation.co.kr");

	server = *(IN_ADDR*)h->h_addr_list[0];

	return server;
}

int IP_Location(IN_ADDR server, IN_ADDR input_ipaddr, char* output_homeaddr, CRITICAL_SECTION* pcs) {

	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
	SOCKADDR_IN sv = { 0, };

	char elementset[512] = { 0, };
	char request[32768] = { 0, };
	char buffer[65535] = { 0, };
	int reqlen;
	int ressize;
	int err;
	char home[128] = { 0, };
	WCHAR home_uni[128];
	char decoded_home[128];
	sv.sin_addr = server;
	sv.sin_family = AF_INET;
	sv.sin_port = htons(80);

	sprintf(elementset, elements, inet_ntoa(input_ipaddr));
	sprintf(request, form, strlen(elementset) + strlen(view_state) - 1, view_state, elementset);

	reqlen = strlen(request);

	connect(s, (SOCKADDR*)&sv, sizeof(SOCKADDR));
	sendall(s, request, strlen(request));
	ressize = httprecvall(s, buffer, sizeof(buffer));

	err = Get_HomeAddr(buffer, ressize, home, sizeof(home));
	if (err == -1) return err;

	//utf encode - decode
	UTF8ToUnicode((WCHAR*)home, home_uni);
	memset(home, 0, sizeof(home));
	UnicodeToAnsi(home_uni, home);
	////

	EnterCriticalSection(pcs);
	memcpy_s(output_homeaddr, 128, decoded_home, 128);
	LeaveCriticalSection(pcs);
	closesocket(s);

	return 0;
}