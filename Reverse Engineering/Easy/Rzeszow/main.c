
int main(uint param_1,long param_2)

{
  uint uVar1;
  char cVar2;
  byte *__s;
  bool bVar3;
  int iVar4;
  int iVar5;
  size_t sVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  int *piVar12;
  char cVar13;
  ulong uVar14;
  int iVar15;
  long in_FS_OFFSET;
  bool bVar16;
  bool bVar17;
  byte bVar18;
  undefined4 local_58;
  char local_54;
  char local_53;
  char local_52;
  char local_51;
  char local_50;
  char local_4f;
  long local_40;

  bVar18 = 0;
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  puts("Welcome to the CTFlearn Rzeszow Reversing Challenge! v2");
  if (param_1 == 1) {
    iVar4 = 1;
    puts("Usage: Rzeszow CTFlearn{kernel}");
  }
  else {
    __s = *(byte **)(param_2 + 8);
    sVar6 = strlen((char *)__s);
    bVar17 = param_1 == 3;
    bVar3 = false;
    if (bVar17) {
      iVar4 = strncmp(*(char **)(param_2 + 0x10),"-v",2);
      bVar17 = iVar4 == 0;
      bVar3 = bVar17;
    }
    bVar16 = param_1 < 3;
    lVar7 = 9;
    pbVar10 = (byte *)"CTFlearn{";
    pbVar11 = __s;
    do {
      if (lVar7 == 0) break;
      lVar7 = lVar7 + -1;
      bVar16 = *pbVar10 < *pbVar11;
      bVar17 = *pbVar10 == *pbVar11;
      pbVar10 = pbVar10 + (ulong)bVar18 * -2 + 1;
      pbVar11 = pbVar11 + (ulong)bVar18 * -2 + 1;
    } while (bVar17);
    cVar13 = (!bVar16 && !bVar17) - bVar16;
    iVar4 = (int)cVar13;
    if (cVar13 == '\0') {
      if (__s[sVar6 - 1] == 0x7d) {
        if (sVar6 == 0x14) {
          piVar12 = &local_58;
          for (lVar7 = 5; lVar7 != 0; lVar7 = lVar7 + -1) {
            *piVar12 = iVar4;
            piVar12 = piVar12 + (ulong)bVar18 * -2 + 1;
          }
          strncpy((char *)&local_58,(char *)(__s + 9),10);
          __printf_chk(1,"Flag kernel is: %s\n",&local_58);
          if (bVar3) {
            uVar14 = 0;
            __printf_chk(1,"The flag is hidden in here somewhere: \n%s\n\n",kernelenc);
            iVar5 = 0;
            do {
              uVar1 = iVar5 + 0xbaadf00d;
              cVar13 = *(char *)((long)&local_58 + uVar14);
              iVar15 = (int)cVar13;
              __printf_chk(1,"input  char-> i  : %2d, c  : \'%c\' ascii value: %2d\n",
                           uVar14 & 0xffffffff,iVar15,iVar15);
              uVar9 = iVar15 * iVar15 * iVar15 + iVar15 * iVar15 + iVar5;
              iVar5 = iVar5 + 3;
              uVar8 = (ulong)(uVar1 % uVar9 & 0x1ff);
              cVar2 = kernelenc[uVar8];
              __printf_chk(1,"hidden char-> pos: %2d, enc: \'%c\'\n\n",uVar8,(int)cVar2);
              if (cVar13 != cVar2) {
                iVar4 = 5;
                puts("Sorry, bad flag dude!");
                __printf_chk(1,
                             "Entered flag kernel character \'%c\' does not match encrypted string c haracter \'%c\'\n"
                             ,iVar15,(int)cVar2);
                goto LAB_001013cb;
              }
              uVar14 = uVar14 + 1;
              __printf_chk(1,"Woow Woot!! Character %c is a match!!\n\n",iVar15);
            } while (iVar5 != 0x1e);
          }
          else {
            iVar5 = (int)(char)local_58;
            if (((((((char)local_58 !=
                     kernelenc[(uint)(0xbaadf00d %
                                     (ulong)(uint)(iVar5 * iVar5 + iVar5 * iVar5 * iVar5)) & 0x1ff ])
                   || (iVar5 = (int)local_58._1_1_,
                      local_58._1_1_ !=
                      kernelenc[(uint)(0xbaadf010 %
                                      (ulong)(uint)(iVar5 * iVar5 + 3 + iVar5 * iVar5 * iVar5)) &
                                0x1ff])) ||
                  (iVar5 = (int)local_58._2_1_,
                  local_58._2_1_ !=
                  kernelenc[(uint)(0xbaadf013 %
                                  (ulong)(uint)(iVar5 * iVar5 + 6 + iVar5 * iVar5 * iVar5)) & 0x1f f]
                  )) || ((iVar5 = (int)local_58._3_1_,
                         local_58._3_1_ !=
                         kernelenc[(uint)(0xbaadf016 %
                                         (ulong)(uint)(iVar5 * iVar5 + 9 + iVar5 * iVar5 * iVar5))  &
                                   0x1ff] ||
                         (iVar5 = (int)local_54,
                         local_54 !=
                         kernelenc[(uint)(0xbaadf019 %
                                         (ulong)(uint)(iVar5 * iVar5 + 0xc + iVar5 * iVar5 * iVar5 ))
                                   & 0x1ff])))) ||
                ((iVar5 = (int)local_53,
                 local_53 !=
                 kernelenc[(uint)(0xbaadf01c %
                                 (ulong)(uint)(iVar5 * iVar5 + 0xf + iVar5 * iVar5 * iVar5)) & 0x1 ff
                          ] ||
                 ((iVar5 = (int)local_52,
                  local_52 !=
                  kernelenc[(uint)(0xbaadf01f %
                                  (ulong)(uint)(iVar5 * iVar5 + 0x12 + iVar5 * iVar5 * iVar5)) &
                            0x1ff] ||
                  (iVar5 = (int)local_51,
                  local_51 !=
                  kernelenc[(uint)(0xbaadf022 %
                                  (ulong)(uint)(iVar5 * iVar5 + 0x15 + iVar5 * iVar5 * iVar5)) &
                            0x1ff])))))) ||
               ((iVar5 = (int)local_50,
                local_50 !=
                kernelenc[(uint)(0xbaadf025 %
                                (ulong)(uint)(iVar5 * iVar5 + 0x18 + iVar5 * iVar5 * iVar5)) & 0x1 ff
                         ] ||
                (iVar5 = (int)local_4f,
                kernelenc[(uint)(0xbaadf028 %
                                (ulong)(uint)(iVar5 * iVar5 + 0x1b + iVar5 * iVar5 * iVar5)) & 0x1 ff
                         ] != local_4f)))) {
              iVar4 = 5;
              puts("Sorry, bad flag dude!");
              goto LAB_001013cb;
            }
          }
          __printf_chk(1,"Woot Woot, you found the flag: %s\n",__s);
        }
        else {
          iVar4 = 4;
          puts("Error: Your flag is the wrong length dude!");
        }
      }
      else {
        iVar4 = 3;
        puts("Error: The flag must end with }");
      }
    }
    else {
      iVar4 = 2;
      puts("Error: The flag must begin with CTFlearn{");
    }
  }
LAB_001013cb:
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar4;
}

