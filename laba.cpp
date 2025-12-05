#include <iostream>
#include <string>

using namespace std;

string removeLeadingZeros(string numberString) {
  while (numberString.size() > 1 && numberString[0] == '0') {
    numberString.erase(0, 1);
  }
  return numberString;
}

int compareStrings(string firstNumberString, string secondNumberString) {

  if (firstNumberString.size() < secondNumberString.size()) {
    return -1;
  }
  if (firstNumberString.size() > secondNumberString.size()) {
    return 1;
  }

  int currentIndex;
  currentIndex = 0;
  while (currentIndex < firstNumberString.size()) {
    if (firstNumberString[currentIndex] < secondNumberString[currentIndex]) {
      return -1;
    }
    if (firstNumberString[currentIndex] > secondNumberString[currentIndex]) {
      return 1;
    }
    
    ++currentIndex;
  }

  return 0;
}

string addStrings(string firstNumberString, string secondNumberString) {
  string resultString;
  resultString = "";

  int indexFirstNumber;
  int indexSecondNumber;
  int carryValue;
  int sumValue;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int newDigitValue;
  char newDigitChar;

  indexFirstNumber = firstNumberString.size() - 1;
  indexSecondNumber = secondNumberString.size() - 1;
  carryValue = 0;

  while (indexFirstNumber >= 0 || indexSecondNumber >= 0 || carryValue > 0) {
    sumValue = carryValue;
    digitValueFirstNumber = 0;
    digitValueSecondNumber = 0;

    if (indexFirstNumber >= 0) {
      digitValueFirstNumber = firstNumberString[indexFirstNumber] - '0';
      sumValue = sumValue + digitValueFirstNumber;
    }

    if (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumberString[indexSecondNumber] - '0';
      sumValue = sumValue + digitValueSecondNumber;
    }

    newDigitValue = sumValue % 10;
    newDigitChar = char(newDigitValue + '0');
    resultString = newDigitChar + resultString;
    carryValue = sumValue / 10;

    --indexFirstNumber;
    --indexSecondNumber;
  }

  return resultString;
}

string subtractStrings(string firstNumberString, string secondNumberString) {
  string resultString;
  resultString = "";

  int indexFirstNumber;
  int indexSecondNumber;
  int borrowValue;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int differenceValue;
  char newDigitChar;

  indexFirstNumber = firstNumberString.size() - 1;
  indexSecondNumber = secondNumberString.size() - 1;
  borrowValue = 0;

  while (indexFirstNumber >= 0) {
    digitValueFirstNumber = firstNumberString[indexFirstNumber] - '0';
    digitValueSecondNumber = 0;

    if (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumberString[indexSecondNumber] - '0';
    }

    differenceValue = digitValueFirstNumber - borrowValue - digitValueSecondNumber;

    if (differenceValue < 0) {
      differenceValue = differenceValue + 10;
      borrowValue = 1;
    } else {
      borrowValue = 0;
    }

    newDigitChar = char(differenceValue + '0');
    resultString = newDigitChar + resultString;

    --indexFirstNumber;
    --indexSecondNumber;
  }

  resultString = removeLeadingZeros(resultString);
  return resultString;
}

string multiplyStrings(string firstNumberString, string secondNumberString) {
  int sizeFirstNumber;
  int sizeSecondNumber;
  int indexFirstNumber;
  int indexSecondNumber;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int multiplicationValue;
  int positionRight;
  int positionLeft;
  int currentRightDigitValue;
  int sumLeftRight;
  int newRightDigitValue;
  int carryValue;
  int currentLeftDigitValue;
  string resultString;

  sizeFirstNumber = firstNumberString.size();
  sizeSecondNumber = secondNumberString.size();
  resultString = string(sizeFirstNumber + sizeSecondNumber, '0');
  indexFirstNumber = sizeFirstNumber - 1;

  while (indexFirstNumber >= 0) {
    digitValueFirstNumber = firstNumberString[indexFirstNumber] - '0';
    indexSecondNumber = sizeSecondNumber - 1;

    while (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumberString[indexSecondNumber] - '0';
      multiplicationValue = digitValueFirstNumber * digitValueSecondNumber;
      positionRight = indexFirstNumber + indexSecondNumber + 1;
      positionLeft = indexFirstNumber + indexSecondNumber;
      
      currentRightDigitValue = resultString[positionRight] - '0';
      sumLeftRight = multiplicationValue + currentRightDigitValue;
      newRightDigitValue = sumLeftRight % 10;
      carryValue = sumLeftRight / 10;
      resultString[positionRight] = char(newRightDigitValue + '0');
      
      currentLeftDigitValue = resultString[positionLeft] - '0';
      currentLeftDigitValue = currentLeftDigitValue + carryValue;
      resultString[positionLeft] = char(currentLeftDigitValue + '0');

      --indexSecondNumber;
    }

    --indexFirstNumber;
  }

  resultString = removeLeadingZeros(resultString);
  
  return resultString;
}

string divideStrings(string dividendString, string divisorString) {
  string resultString;
  string currentValueString;
  string nextDigitString;
  string multiplicationResultString;
  string multiplicationDigitString;
  string multiplicationProductString;
  int indexCurrentDigit;
  int quotientDigitValue;
  int nextDigitValue;
  int comparisonResult;
  char nextDigitCharForMultiply;
  char nextDigitChar;
  char quotientDigitChar;
  char multiplicationDigitChar;

  resultString = "";
  currentValueString = "0";
  indexCurrentDigit = 0;

  while (indexCurrentDigit < dividendString.size()) {
    if (currentValueString == "0") {
      currentValueString = "";
    }

    nextDigitChar = dividendString[indexCurrentDigit];
    currentValueString = currentValueString + nextDigitChar;
    currentValueString = removeLeadingZeros(currentValueString);
    quotientDigitValue = 0;

    while (quotientDigitValue < 9) {
      nextDigitValue = quotientDigitValue + 1;
      nextDigitCharForMultiply = char(nextDigitValue + '0');
      nextDigitString = "";
      nextDigitString = nextDigitString + nextDigitCharForMultiply;
      multiplicationResultString = multiplyStrings(divisorString, nextDigitString);
      comparisonResult = compareStrings(multiplicationResultString, currentValueString);

      if (comparisonResult <= 0) {
        ++quotientDigitValue;
      } else {
        break;
      }
    }

    quotientDigitChar = char(quotientDigitValue + '0');
    resultString = resultString + quotientDigitChar;
    multiplicationDigitString = "";
    multiplicationDigitChar = char(quotientDigitValue + '0');
    multiplicationDigitString = multiplicationDigitChar;
    multiplicationProductString = multiplyStrings(divisorString, multiplicationDigitString);
    currentValueString = subtractStrings(currentValueString, multiplicationProductString);

    ++indexCurrentDigit;
  }

  resultString = removeLeadingZeros(resultString);
  return resultString;
}

int main() {
  string firstNumberString;
  string secondNumberString;
  char operationSymbol;

  cout << " Enter first integer: ";
  cin >> firstNumberString;
  cout << " Enter operation (+, -, *, /, <, >, =): ";
  cin >> operationSymbol;
  cout << " Enter second integer: ";
  cin >> secondNumberString;

  if (operationSymbol == '+') {
    string resultString;
    
    resultString = addStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " + " << secondNumberString << " = " << resultString << endl;
  }

  if (operationSymbol == '-') {
    string resultString;
    
    resultString = subtractStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " - " << secondNumberString << " = " << resultString << endl;
  }

  if (operationSymbol == '*') {
    string resultString;
    
    resultString = multiplyStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " * " << secondNumberString << " = " << resultString << endl;
  }

  if (operationSymbol == '/') {
    string resultString;
    
    resultString = divideStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " / " << secondNumberString << " = " << resultString << endl;
  }

  if (operationSymbol == '>') {
    int comparisonResult;
    
    comparisonResult = compareStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " > " << secondNumberString << " : ";
    
    if (comparisonResult == 1) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  if (operationSymbol == '<') {
    int comparisonResult;
    
    comparisonResult = compareStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " < " << secondNumberString << " : ";
    
    if (comparisonResult == -1) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  if (operationSymbol == '=') {
    int comparisonResult;
    
    comparisonResult = compareStrings(firstNumberString, secondNumberString);
    
    cout << firstNumberString << " = " << secondNumberString << " : ";
    
    if (comparisonResult == 0) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  return 0;
}

