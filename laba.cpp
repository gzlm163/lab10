#include <iostream>
#include <string>

using namespace std;

string removeLeadingZeros(string numberString) {
  while (numberString.size() > 1 && numberString[0] == '0') {
    numberString.erase(0, 1);
  }
  return numberString;
}


int compareNumbers(string firstNumber, string secondNumber) {

  if (firstNumber.size() < secondNumber.size()) {
    return -1;
  }
  if (firstNumber.size() > secondNumber.size()) {
    return 1;
  }

  int currentIndex;
  currentIndex = 0;
  while (currentIndex < firstNumber.size()) {
    if (firstNumber[currentIndex] < secondNumber[currentIndex]) {
      return -1;
    }
    if (firstNumber[currentIndex] > secondNumber[currentIndex]) {
      return 1;
    }
    
    ++currentIndex;
  }

  return 0;
}

string addNumbers(string firstNumber, string secondNumber) {
  string resultString;
  resultString = "";

  int indexFirstNumber;
  int indexSecondNumber;
  int carryDigit;
  int sumCurrentDigits;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int newDigitValue;
  char newDigitChar;

  indexFirstNumber = firstNumber.size() - 1;
  indexSecondNumber = secondNumber.size() - 1;
  carryDigit = 0;

  while (indexFirstNumber >= 0 || indexSecondNumber >= 0 || carryDigit > 0) {
    sumCurrentDigits = carryDigit;
    digitValueFirstNumber = 0;
    digitValueSecondNumber = 0;

    if (indexFirstNumber >= 0) {
      digitValueFirstNumber = firstNumber[indexFirstNumber] - '0';
      sumCurrentDigits = sumCurrentDigits + digitValueFirstNumber;
    }

    if (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumber[indexSecondNumber] - '0';
      sumCurrentDigits = sumCurrentDigits + digitValueSecondNumber;
    }

    newDigitValue = sumCurrentDigits % 10;
    newDigitChar = char(newDigitValue + '0');
    resultString = newDigitChar + resultString;
    carryDigit = sumCurrentDigits / 10;

    --indexFirstNumber;
    --indexSecondNumber;
  }

  return resultString;
}

string subtractNumber(string firstNumber, string secondNumber) {
  string resultString;
  resultString = "";

  int indexFirstNumber;
  int indexSecondNumber;
  int borrowValue;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int difference;
  char newDigitChar;

  indexFirstNumber = firstNumber.size() - 1;
  indexSecondNumber = secondNumber.size() - 1;
  borrowValue = 0;

  while (indexFirstNumber >= 0) {
    digitValueFirstNumber = firstNumber[indexFirstNumber] - '0';
    digitValueSecondNumber = 0;

    if (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumber[indexSecondNumber] - '0';
    }

    difference = digitValueFirstNumber - borrowValue - digitValueSecondNumber;

    if (difference < 0) {
      difference = difference + 10;
      borrowValue = 1;
    } else {
      borrowValue = 0;
    }

    newDigitChar = char(difference + '0');
    resultString = newDigitChar + resultString;

    --indexFirstNumber;
    --indexSecondNumber;
  }

  resultString = removeLeadingZeros(resultString);
  return resultString;
}

string multiplyNumbers(string firstNumber, string secondNumber) {
  int sizeFirstNumber;
  int sizeSecondNumber;
  int indexFirstNumber;
  int indexSecondNumber;
  int digitValueFirstNumber;
  int digitValueSecondNumber;
  int multiplicationValue;
  int unitsPosition;
  int tensPosition;
  int currentUnitsValue;
  int sumBeforeCarry;
  int newUnitsDigit;
  int carryDigit;
  int currentTensDigit;
  string resultString;

  sizeFirstNumber = firstNumber.size();
  sizeSecondNumber = secondNumber.size();
  resultString = string(sizeFirstNumber + sizeSecondNumber, '0');
  indexFirstNumber = sizeFirstNumber - 1;

  while (indexFirstNumber >= 0) {
    digitValueFirstNumber = firstNumber[indexFirstNumber] - '0';
    indexSecondNumber = sizeSecondNumber - 1;

    while (indexSecondNumber >= 0) {
      digitValueSecondNumber = secondNumber[indexSecondNumber] - '0';
      multiplicationValue = digitValueFirstNumber * digitValueSecondNumber;
      unitsPosition = indexFirstNumber + indexSecondNumber + 1;
      tensPosition = indexFirstNumber + indexSecondNumber;
      
      currentUnitsValue = resultString[unitsPosition] - '0';
      sumBeforeCarry = multiplicationValue + currentUnitsValue;
      newUnitsDigit = sumBeforeCarry % 10;
      carryDigit = sumBeforeCarry / 10;
      resultString[unitsPosition] = char(newUnitsDigit + '0');
      
      currentTensDigit = resultString[tensPosition] - '0';
      currentTensDigit = currentTensDigit + carryDigit;
      resultString[tensPosition] = char(currentTensDigit + '0');

      --indexSecondNumber;
    }

    --indexFirstNumber;
  }

  resultString = removeLeadingZeros(resultString);
  
  return resultString;
}

string divideNumber(string dividend, string divisor) {
  string resultString;
  string currentDividend;
  string checkDigit;
  string trialProduct;
  string digitToMultiply;
  string productToSubtract;
  int indexCurrentDigit;
  int quotientDigit;
  int nextDigitValue;
  int comparisonResult;
  char nextDigitCharForMultiply;
  char nextDigitChar;
  char quotientDigitChar;
  char multiplicationDigitChar;

  resultString = "";
  currentDividend = "0";
  indexCurrentDigit = 0;

  while (indexCurrentDigit < dividend.size()) {
    if (currentDividend == "0") {
      currentDividend = "";
    }

    nextDigitChar = dividend[indexCurrentDigit];
    currentDividend = currentDividend + nextDigitChar;
    currentDividend = removeLeadingZeros(currentDividend);
    quotientDigit = 0;

    while (quotientDigit < 9) {
      nextDigitValue = quotientDigit + 1;
      nextDigitCharForMultiply = char(nextDigitValue + '0');
      checkDigit = "";
      checkDigit = checkDigit + nextDigitCharForMultiply;
      trialProduct = multiplyNumbers(divisor, checkDigit);
      comparisonResult = compareNumbers(trialProduct, currentDividend);

      if (comparisonResult <= 0) {
        ++quotientDigit;
      } else {
        break;
      }
    }

    quotientDigitChar = char(quotientDigit + '0');
    resultString = resultString + quotientDigitChar;
    digitToMultiply = "";
    multiplicationDigitChar = char(quotientDigit + '0');
    digitToMultiply = multiplicationDigitChar;
    productToSubtract = multiplyNumbers(divisor, digitToMultiply);
    currentDividend = subtractNumber(currentDividend, productToSubtract);

    ++indexCurrentDigit;
  }

  resultString = removeLeadingZeros(resultString);
  return resultString;
}

int main() {
  string firstNumber;
  string secondNumber;
  char operationSymbol;

  cout << " Enter first integer: ";
  cin >> firstNumber;
  cout << " Enter operation (+, -, *, /, <, >, =): ";
  cin >> operationSymbol;
  cout << " Enter second integer: ";
  cin >> secondNumber;

  if (operationSymbol == '+') {
    string resultString;
    
    resultString = addNumbers(firstNumber, secondNumber);
    
    cout << firstNumber << " + " << secondNumber << " = " << resultString << endl;
  }

  if (operationSymbol == '-') {
    string resultString;
    
    resultString = subtractNumber(firstNumber, secondNumber);
    
    cout << firstNumber << " - " << secondNumber << " = " << resultString << endl;
  }

  if (operationSymbol == '*') {
    string resultString;
    
    resultString = multiplyNumbers(firstNumber, secondNumber);
    
    cout << firstNumber << " * " << secondNumber << " = " << resultString << endl;
  }

  if (operationSymbol == '/') {
    string resultString;
    
    resultString = divideNumber(firstNumber, secondNumber);
    
    cout << firstNumber << " / " << secondNumber << " = " << resultString << endl;
  }

  if (operationSymbol == '>') {
    int comparisonResult;
    
    comparisonResult = compareNumbers(firstNumber, secondNumber);
    
    cout << firstNumber << " > " << secondNumber << " : ";
    
    if (comparisonResult == 1) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  if (operationSymbol == '<') {
    int comparisonResult;
    
    comparisonResult = compareNumbers(firstNumber, secondNumber);
    
    cout << firstNumber << " < " << secondNumber << " : ";
    
    if (comparisonResult == -1) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  if (operationSymbol == '=') {
    int comparisonResult;
    
    comparisonResult = compareNumbers(firstNumber, secondNumber);
    
    cout << firstNumber << " = " << secondNumber << " : ";
    
    if (comparisonResult == 0) {
      cout << " true " << endl;
    } else {
      cout << " false " << endl;
    }
  }

  return 0;
}


