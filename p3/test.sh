#!/bin/bash
FAIL=0

# Function to run a test. The test command should be stured in cmd.sh before
# calling this function.
runTest() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt stderr.txt

  # Wrtie the command to a file, so we can get the interpretetaton of quotes
  # the way we need.  There's probably a better way to do this.
  echo "./match "${args[@]}" > output.txt 2> stderr.txt" > cmd.sh

  # Report the command we're about to run.
  echo -n "Test $TESTNO: "
  cat cmd.sh

  # Run it.
  chmod +x cmd.sh
  ./cmd.sh
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if [ $ESTATUS -eq 0 ] &&
	 ! diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output to stdout didn't match expected."
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if [ $ESTATUS -ne 0 ] &&
	 ! diff -q error-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output to stderr didn't match expected error message."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Try to get a fresh compile of the project.
make clean
make
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your program."
    FAIL=1
fi

# Run individual tests.
if [ -x match ] ; then
    args=(\'abc\' file-a.txt)
    runTest 01 0
    
    args=(\'xyz\' file-a.txt)
    runTest 02 0
    
    args=(\'?Z\' file-b.txt)
    runTest 03 0
    
    args=(\'a???w\' file-c.txt)
    runTest 04 0
    
    args=(\'??_??\' file-c.txt)
    runTest 05 0
    
    args=(\'?????\' file-c.txt)
    runTest 06 0
    
    args=(-n \'IT\' file-b.txt)
    runTest 07 0
    
    args=(-n \'?????\' file-c.txt)
    runTest 08 0
    
    args=(\'*\' file-b.txt)
    runTest 09 0
    
    args=(\'z*\' file-c.txt)
    runTest 10 0
    
    args=(\'*a*\' file-c.txt)
    runTest 11 0
    
    args=(\'*.mp3\' file-d.txt)
    runTest 12 0
    
    args=(\'*-b*\' file-d.txt)
    runTest 13 0
    
    args=(-v -n \'big-*\' file-d.txt)
    runTest 14 0
    
    args=(\'ab*d?f\' file-e.txt)
    runTest 15 0
    
    args=(\'A*\' file-f.txt)
    runTest 16 0
    
    args=(-n \'A*\' file-f.txt)
    runTest 17 0
    
    args=(\'a**b\' file-c.txt)
    runTest 18 1
    
    args=(-n -x -v \'A?\' file-b.txt)
    runTest 19 1
    
    args=(\'abc\' not-a-real-file.txt)
    runTest 20 1
    
    args=(\'*1*\' file-f.txt)
    runTest 21 1
	  
    args=(\'xyz\' file-g.txt)
    runTest 22 1
else
    echo "**** Your program didnt compile successfully, so it couldn't be tested."
    FAIL=1
fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
