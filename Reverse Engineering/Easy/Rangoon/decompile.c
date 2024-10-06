
undefined4 main(int param_1,long param_2)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte *__s;
  int iVar4;
  clock_t cVar5;
  size_t sVar6;
  long lVar7;
  clock_t cVar8;
  long lVar9;
  ulong uVar10;
  byte *pbVar11;
  undefined8 *puVar12;
  byte *pbVar13;
  undefined8 *puVar14;
  undefined4 uVar15;
  bool bVar16;
  bool bVar17;
  byte bVar18;
  
  bVar18 = 0;
  cVar5 = clock();
  FillInStrings();
  puVar12 = &buffer;
  for (lVar9 = 0x20; lVar9 != 0; lVar9 = lVar9 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + (ulong)bVar18 * -2 + 1;
  }
  __printf_chk(1,"%s\n\n",WelcomeMsg);
  puts("Compile Options: ${CMAKE_CXX_FLAGS} -O0 -fno-stack-protector -mno-sse");
  bVar16 = param_1 == 0;
  bVar17 = param_1 == 1;
  if (bVar17) {
    __printf_chk(1,"%s\n\n",UsageMsg);
    uVar15 = 1;
  }
  else {
    __s = *(byte **)(param_2 + 8);
    lVar9 = 9;
    pbVar11 = __s;
    pbVar13 = (byte *)"CTFlearn{";
    do {
      if (lVar9 == 0) break;
      lVar9 = lVar9 + -1;
      bVar16 = *pbVar11 < *pbVar13;
      bVar17 = *pbVar11 == *pbVar13;
      pbVar11 = pbVar11 + (ulong)bVar18 * -2 + 1;
      pbVar13 = pbVar13 + (ulong)bVar18 * -2 + 1;
    } while (bVar17);
    if ((!bVar16 && !bVar17) == bVar16) {
      sVar6 = strlen((char *)__s);
      if (__s[sVar6 - 1] == 0x7d) {
        bVar2 = __s[0x11];
        bVar3 = __s[0x16];
        uVar10 = 0xffffffffffffffff;
        puVar14 = &buffer;
        do {
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          cVar1 = *(char *)puVar14;
          puVar14 = (undefined8 *)((long)puVar14 + (ulong)bVar18 * -2 + 1);
        } while (cVar1 != '\0');
        uVar10 = ~uVar10;
        *(undefined8 *)(uVar10 + 0x1040df) = 0x6e7261656c465443;
        lVar9 = strings;
        *(undefined2 *)((long)&buffer + uVar10 + 7) = 0x7b;
        lVar7 = __stpcpy_chk((long)&DAT_001040e8 + uVar10,
                             *(undefined8 *)(lVar9 + (ulong)((bVar2 == 0x5f) + 2) * 8),
                             (long)puVar12 - ((long)&DAT_001040e8 + uVar10));
        lVar7 = __memcpy_chk(lVar7,&DAT_0010200e,2,(long)puVar12 - lVar7);
        lVar7 = __stpcpy_chk(lVar7 + 1,*(undefined8 *)(lVar9 + ((ulong)(bVar3 == 0x5f) * 5 + 3) *  8)
                             ,(long)&DAT_001041df - lVar7);
        lVar7 = __memcpy_chk(lVar7,&DAT_0010200e,2,(long)puVar12 - lVar7);
        lVar9 = __stpcpy_chk(lVar7 + 1,*(undefined8 *)(lVar9 + ((ulong)(sVar6 == 0x1c) * 3 + 9) *  8)
                             ,(long)&DAT_001041df - lVar7);
        lVar9 = __memcpy_chk(lVar9,"}",2,(long)puVar12 - lVar9);
        if (lVar9 == 0x1040fb) {
          iVar4 = strcmp((char *)__s,(char *)&buffer);
          if (iVar4 == 0) {
            __printf_chk(1,"%s %s\n\n",CongratsMsg,__s);
            cVar8 = clock();
            __printf_chk(1,"Elapsed time in clock ticks: %ld\n",cVar8 - cVar5);
            __printf_chk(1,"%s\n\n",AllDoneMsg);
            uVar15 = 0;
          }
          else {
            uVar15 = 5;
            __printf_chk(1,"%s\n\n",WrongFlagMsg);
          }
        }
        else {
          uVar15 = 3;
          __printf_chk(1,"%s\n\n",WrongFlagMsg);
        }
      }
      else {
        uVar15 = 4;
        __printf_chk(1,"%s\n\n",WrongFlagMsg);
      }
    }
    else {
      uVar15 = 2;
      __printf_chk(1,"%s\n\n",WrongFlagMsg);
    }
  }
  return uVar15;
}
