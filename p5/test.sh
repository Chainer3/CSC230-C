#!/bin/bash
# This is a shell script to check your program(s) on test cases.
# It usese the same language you normally use to type commands in
# a terminal window.  You can write whole programs in shell.

# Assume we've succeeded until we see otherwise.
FAIL=0

# Check the exit status.  The actual exit status (ASTATUS) should match
# the expected status (ESTATUS)
checkStatus() {
  ESTATUS="$1"
  ASTATUS="$2"

  # Make sure the program exited with the right exit status.
  if [ "$ASTATUS" -ne "$ESTATUS" ]; then
      echo "**** Test FAILED - incorrect program exit status. (expected $ESTATUS,  Got: $ASTATUS)"
      return 1
  fi

  return 0
}

# Check the contents of an a file.  If the expected file (EFILE)
# exists, then the actual file (AFILE) should exist and it should match.
checkFile() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"

  # Make sure we're really expecting this file.
  if [ ! -f "$EFILE" ]; then
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should be empty.
checkFileOrEmpty() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"
  
  # if the expected output file doesn't exist, the actual file should be
  # empty.
  if [ ! -f "$EFILE" ]; then
      if [ -s "$AFILE" ]; then
	  echo "**** Test FAILED - $NAME ($AFILE) should be empty."
	  return 1
      fi
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should not exist.
checkFileOrDNE() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"
  
  # if the expected output file doesn't exist, the actual file should be
  # empty.
  if [ ! -f "$EFILE" ]; then
      if [ -f "$AFILE" ]; then
	  echo "**** Test FAILED - $NAME ($AFILE) should not be created."
	  return 1
      fi
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Test the deflate program.
testDeflate() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output stdout.txt stderr.txt

  echo "deflate test $TESTNO: ./deflate ${args[@]} original-$TESTNO output > stdout.txt 2> stderr.txt"
  ./deflate ${args[@]} original-$TESTNO output > stdout.txt 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFileOrDNE "Compressed Output" "compressed-$TESTNO" "output" ||
     ! checkFileOrEmpty "Standard Output" "expected-d$TESTNO.txt" "stdout.txt" ||
     ! checkFileOrEmpty "Error Output" "error-d$TESTNO.txt" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Test the inflate program.
testInflate() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output stdout.txt stderr.txt

  echo "inflate test $TESTNO: ./inflate ${args[@]} compressed-$TESTNO output > stdout.txt 2> stderr.txt"
  ./inflate ${args[@]} compressed-$TESTNO output > stdout.txt 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFileOrDNE "De-compressed Output" "original-$TESTNO" "output" ||
     ! checkFileOrEmpty "Standard Output" "expected-i$TESTNO.txt" "stdout.txt" ||
     ! checkFileOrEmpty "Error Output" "error-i$TESTNO.txt" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make exited unsuccessfully"
  FAIL=1
fi

# Test the deflate program
echo
echo "Testing deflate"
if [ -x deflate ]; then
    args=(-b 8)
    testDeflate 01 0
    
    args=()
    testDeflate 02 0
    
    args=(-d)
    testDeflate 03 0
    
    args=(-d)
    testDeflate 04 0
    
    args=(-d)
    testDeflate 05 0
    
    args=(-d)
    testDeflate 06 0
    
    args=()
    testDeflate 07 0
    
    args=(-b 11)
    testDeflate 08 0
    
    args=(-d)
    testDeflate 09 0
    
    args=()
    testDeflate 10 0
    
    args=()
    testDeflate 11 1
    
    args=(-bad-argument)
    testDeflate 12 1
else
  echo "Since your deflate program didn't compile, we couldn't test it"
fi

# Test the inflate program
echo
echo "Testing inflate"
if [ -x inflate ]; then
    args=(-b 8)
    testInflate 01 0
    
    args=()
    testInflate 02 0
    
    args=(-d)
    testInflate 03 0
    
    args=(-d)
    testInflate 04 0
    
    args=(-d)
    testInflate 05 0
    
    args=(-d)
    testInflate 06 0
    
    args=()
    testInflate 07 0
    
    args=(-b 11)
    testInflate 08 0
    
    args=(-d)
    testInflate 09 0
    
    args=()
    testInflate 10 0
    
    args=()
    testInflate 13 1
else
  echo "Since your inflate program didn't compile, we couldn't test it"
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "TESTS SUCCESSFUL"
  exit 0
fi
