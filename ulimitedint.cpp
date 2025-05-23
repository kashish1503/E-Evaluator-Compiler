/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>

using namespace std;

UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 0;
    capacity = 10;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
}

UnlimitedInt::UnlimitedInt(string s) : size(s.size()), capacity(s.size() + 1) {
    if (s.empty()) {
        size = 1;
        sign = 0;
    } else {
        if (s[0] == '-') {
            s.erase(0, 1);
            size--;
            sign = -1;
        } else {
            sign = 1;
        }

        unlimited_int = new int[capacity];

        for (int i = 0; i < size; i++) {
            unlimited_int[i] = s[size - i - 1] - '0';
        }

        int k = size - 1;
        while (k > 0 && unlimited_int[k] == 0) {
            size = k;
            k--;
        }
        if (size == 1 && unlimited_int[0] == '0') sign = 0;
    }
}

UnlimitedInt::UnlimitedInt(int i) {
    capacity = 10;
    if (i < 0) {
        sign = -1;
        i = -i;
    } 
    else if (i > 0) sign = 1;
    if (i==0) {
        size = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
        sign = 0;
        return;
    }

    int j = i;
    size = 0;
    while (j > 0) {
        j /= 10;
        size++;
    }

    unlimited_int = new int[capacity];

    for (int j = 0; j < size; j++) {
        unlimited_int[j] = i % 10;
        i /= 10;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    sign = sgn;
    size = sz;
    capacity = cap;

    if (size > capacity) {
        unlimited_int = new int[size];
        capacity = size;
    } else {
        unlimited_int = new int[capacity];
    }

    for (int i = 0; i < size; i++) {
        unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}


    // Return the size of the unlimited int
int UnlimitedInt::get_size(){
    return size;
};

// Return the unlimited_int array
int* UnlimitedInt::get_array(){
    return unlimited_int;
};

// Get sign
int UnlimitedInt::get_sign(){
    return sign;
};

// Get capacity
int UnlimitedInt::get_capacity(){
    return capacity;
};

bool larger_int(UnlimitedInt* i1, UnlimitedInt* i2){
    int* x1 = i1->get_array();
    int* x2 = i2->get_array();
    if (i1->get_size() > i2->get_size()) return true;
    if (i1->get_size() < i2->get_size()) return false;
    for (int i=i1->get_size()-1; i>=0; i--){
        if (x1[i] > x2[i]) return true;
        if (x1[i] < x2[i]) return false;
    }
    return true;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    // Determine the signs of the operands
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    // Determine the larger and smaller operands
    UnlimitedInt* larger = larger_int(i1, i2) ? i1 : i2;
    UnlimitedInt* smaller = larger == i1 ? i2 : i1;

    if (sign1 != sign2){
        if (larger->sign == -1) {
            UnlimitedInt* neg = new UnlimitedInt();
            neg->capacity = larger->capacity;
            neg->size = larger->size;
            neg->unlimited_int = larger->get_array();
            neg->sign = 1;
            return sub(smaller, neg);
        }
        else {
            UnlimitedInt* neg = new UnlimitedInt();
            neg->capacity = smaller->capacity;
            neg->size = smaller->size;
            neg->unlimited_int = smaller->get_array();
            neg->sign = 1;
            return sub(larger, neg);
        }
    }

    int carry = 0;
    UnlimitedInt* result = new UnlimitedInt();
    result->capacity = larger->capacity;
    if (larger->capacity == larger->size) result->capacity *= 2;
    result->size = larger->size;
    delete[] result->unlimited_int;
    result->unlimited_int = new int[result->capacity];
    
    for (int i=0; i<smaller->size; i++){
        int x = larger->get_array()[i] + smaller->get_array()[i] + carry;
        result->get_array()[i] = x%10;
        carry = x > 9 ? 1 : 0;
    }

    for (int i=smaller->size; i < larger->size; i++){
        int x = larger->get_array()[i] + carry;
        result->get_array()[i] = x%10;
        carry = x > 9 ? 1 : 0;
    }

    if (carry == 1) result->get_array()[larger->size] = 1;
    if (carry == 1) result->size++;

    // Determine the sign of the result
    if (sign1 * sign2 == -1) {
        result->sign = larger->sign;
    } else {
        result->sign = sign1;
    }

    // Remove leading zeros from the result
    int k = result->get_size() - 1;
    while (k > 0 && result->get_array()[k] == 0) {
        result->size--;
        k--;
    }

    if (result->get_size() == 1 && result->get_array()[0] == 0) result->sign = 0;
    return result;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    // Determine the signs of the operands
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    // Determine the larger and smaller operands
    UnlimitedInt* larger = (larger_int(i1, i2)) ? i1 : i2;
    UnlimitedInt* smaller = (larger == i1) ? i2 : i1;

    if (sign1 != sign2){
        if (i1->sign == -1){
            UnlimitedInt* neg = new UnlimitedInt();
            neg->capacity = i2->capacity;
            neg->size = i2->size;
            neg->unlimited_int = i2->get_array();
            neg->sign = -1;
            return add(i1, neg);
        }
        else {
            UnlimitedInt* neg = new UnlimitedInt();
            neg->capacity = i2->capacity;
            neg->size = i2->size;
            neg->unlimited_int = i2->get_array();
            neg->sign = 1;
            return add(i1, neg);
        }
    }

    int borrow = 0;
    // Create a result object with the capacity of the larger operand
    UnlimitedInt* result = new UnlimitedInt();
    result->capacity = larger->capacity;
    delete[] result->unlimited_int;
    result->unlimited_int = new int[result->capacity];
    result->size = larger->size;

    // Perform subtraction digit by digit
    for (int i=0; i<smaller->size; i++){
        int y = larger->get_array()[i] - borrow - smaller->get_array()[i];
        int x = y >= 0 ?  y : 10 + y;
        result->get_array()[i] = x;
        borrow = y >= 0 ? 0 : 1;
    }

    for (int i=smaller->size; i<larger->size; i++){
        int x = larger->get_array()[i] - borrow;
        result->get_array()[i] = x >= 0 ? x : 10 + x;
        borrow = x >= 0 ? 0 : 1;
    }

    // Determine the sign of the result
    result->sign = larger == i1 ? sign1 : -sign1;

    // Remove leading zeros from the result
    int k = result->get_size() - 1;
    while (k > 0 && result->get_array()[k] == 0) {
        result->size--;
        k--;
    }
    UnlimitedInt* x = new UnlimitedInt();
    UnlimitedInt* y = new UnlimitedInt(2);
    if (larger_int(x, y)) cout << "kammo" << endl;
    if (result->size == 1 && result->get_array()[0] == 0) result->sign = 0;
    return result;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign() == 0 || i2->get_sign() == 0) return new UnlimitedInt();
    // Determine the sign of the result
    int resultSign = i1->get_sign() * i2->get_sign();

    // Create a result object with an initial capacity
    UnlimitedInt* result = new UnlimitedInt();
    result->capacity = i1->size + i2->size;
    result->size = result->capacity; // Maximum possible size
    delete[] result->unlimited_int;
    result->unlimited_int = new int[result->capacity];
    result->sign = resultSign;

    // Initialize the result array with zeros
    for (int i = 0; i < result->capacity; i++) {
        result->unlimited_int[i] = 0;
    }

    // Perform long multiplication
    for (int i = 0; i < i1->get_size(); i++) {
        int carry = 0;
        for (int j = 0; j < i2->get_size(); j++) {
            int product = i1->get_array()[i] * i2->get_array()[j] + carry + result->unlimited_int[i + j];
            carry = product / 10;
            result->unlimited_int[i + j] = product % 10;
        }
        if (carry > 0) {
            result->unlimited_int[i + i2->get_size()] += carry;
        }
    }

    int k = result->size - 1;
    while (k > 0 && result->get_array()[k] == 0) {
        result->size--;
        k--;
    }

    return result;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    int resultSign = i1->get_sign() * i2->get_sign();

    UnlimitedInt* divisor = i2->get_sign() == 1 ? new UnlimitedInt(i2->to_string()) : mul(i2, new UnlimitedInt(-1));
    UnlimitedInt* dividend = i1->get_sign() == 1 ? new UnlimitedInt(i1->to_string()) : mul(i1, new UnlimitedInt(-1));
    
    // Create result and remainder objects
    int quotient = 0;
    while (larger_int(dividend, divisor)){
        dividend = sub(dividend, divisor);
        quotient++;
    }
    
    UnlimitedInt* result = new UnlimitedInt(quotient);
    result->sign = resultSign;

    return result;
}



UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* quotient = div(i1, i2);
    UnlimitedInt* part = mul(i2, quotient);
    return sub(i1, part);
}

string UnlimitedInt::to_string(){
    string result = "";
    for (int i=size-1; i>=0; i--){
        int temp = unlimited_int[i];
        result += '0' + temp;
    }
    if (sign == -1) result = "-" + result;
    return result;
}