rem   *** validation ***
call scripts\run-validator-tests.bat
call scripts\run-checker-tests.bat

rem    *** tests ***
md tests
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 2" "tests\02" 2
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 3" "tests\03" 3
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 4" "tests\04" 4
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 5" "tests\05" 5
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 6" "tests\06" 6
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 7" "tests\07" 7
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 8" "tests\08" 8
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 9" "tests\09" 9
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 10" "tests\10" 10
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 11" "tests\11" 11
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 12" "tests\12" 12
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 13" "tests\13" 13
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 14" "tests\14" 14
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 15" "tests\15" 15
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 16" "tests\16" 16
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 17" "tests\17" 17
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 18" "tests\18" 18
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 19" "tests\19" 19
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 20" "tests\20" 20
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 21" "tests\21" 21
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 22" "tests\22" 22
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 23" "tests\23" 23
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 24" "tests\24" 24
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 25" "tests\25" 25
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 26" "tests\26" 26
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 27" "tests\27" 27
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 28" "tests\28" 28
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 29" "tests\29" 29
call scripts\gen-input-via-stdout.bat "files\gen3__21_30.exe 30" "tests\30" 30
call scripts\gen-answer.bat tests\01 tests\01.a
call scripts\gen-answer.bat tests\02 tests\02.a
call scripts\gen-answer.bat tests\03 tests\03.a
call scripts\gen-answer.bat tests\04 tests\04.a
call scripts\gen-answer.bat tests\05 tests\05.a
call scripts\gen-answer.bat tests\06 tests\06.a
call scripts\gen-answer.bat tests\07 tests\07.a
call scripts\gen-answer.bat tests\08 tests\08.a
call scripts\gen-answer.bat tests\09 tests\09.a
call scripts\gen-answer.bat tests\10 tests\10.a
call scripts\gen-answer.bat tests\11 tests\11.a
call scripts\gen-answer.bat tests\12 tests\12.a
call scripts\gen-answer.bat tests\13 tests\13.a
call scripts\gen-answer.bat tests\14 tests\14.a
call scripts\gen-answer.bat tests\15 tests\15.a
call scripts\gen-answer.bat tests\16 tests\16.a
call scripts\gen-answer.bat tests\17 tests\17.a
call scripts\gen-answer.bat tests\18 tests\18.a
call scripts\gen-answer.bat tests\19 tests\19.a
call scripts\gen-answer.bat tests\20 tests\20.a
call scripts\gen-answer.bat tests\21 tests\21.a
call scripts\gen-answer.bat tests\22 tests\22.a
call scripts\gen-answer.bat tests\23 tests\23.a
call scripts\gen-answer.bat tests\24 tests\24.a
call scripts\gen-answer.bat tests\25 tests\25.a
call scripts\gen-answer.bat tests\26 tests\26.a
call scripts\gen-answer.bat tests\27 tests\27.a
call scripts\gen-answer.bat tests\28 tests\28.a
call scripts\gen-answer.bat tests\29 tests\29.a
call scripts\gen-answer.bat tests\30 tests\30.a

rem    *** pretests ***
md pretests
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 2" "pretests\02" 2
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 3" "pretests\03" 3
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 4" "pretests\04" 4
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 5" "pretests\05" 5
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 6" "pretests\06" 6
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 7" "pretests\07" 7
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 8" "pretests\08" 8
call scripts\gen-input-via-stdout.bat "files\gen1__2_9.exe 9" "pretests\09" 9
call scripts\gen-input-via-stdout.bat "files\gen2__10_20.exe 10" "pretests\10" 10
call scripts\gen-answer.bat pretests\01 pretests\01.a
call scripts\gen-answer.bat pretests\02 pretests\02.a
call scripts\gen-answer.bat pretests\03 pretests\03.a
call scripts\gen-answer.bat pretests\04 pretests\04.a
call scripts\gen-answer.bat pretests\05 pretests\05.a
call scripts\gen-answer.bat pretests\06 pretests\06.a
call scripts\gen-answer.bat pretests\07 pretests\07.a
call scripts\gen-answer.bat pretests\08 pretests\08.a
call scripts\gen-answer.bat pretests\09 pretests\09.a
call scripts\gen-answer.bat pretests\10 pretests\10.a

