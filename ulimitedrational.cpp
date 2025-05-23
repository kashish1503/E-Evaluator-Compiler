/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include "ulimitedint.h"
#include <iostream>

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b) {
    // Check if a or b is zero
    string a_s = a->to_string();
    string b_s = b->to_string();
    UnlimitedInt* x = a->get_sign() == 1 ? new UnlimitedInt(a_s) : UnlimitedInt::mul(a, new UnlimitedInt(-1));
    UnlimitedInt* y = b->get_sign() == 1 ? new UnlimitedInt(b_s) : UnlimitedInt::mul(b, new UnlimitedInt(-1));

    while (y->get_sign() != 0) {
        UnlimitedInt* temp = x;
        x = y;
        y = UnlimitedInt::mod(temp, y);
    }

    delete y;
    return x;
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt();
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    p = new UnlimitedInt(*num);
    q = new UnlimitedInt(*den);
    UnlimitedInt* g = gcd(p, q);

    p = UnlimitedInt::div(p, g);
    q = UnlimitedInt::div(q, g);
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

std::string UnlimitedRational::get_p_str() {
    return p->to_string();
}

std::string UnlimitedRational::get_q_str() {
    return q->to_string();
}

std::string UnlimitedRational::get_frac_str() {
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    UnlimitedInt* resultNum = UnlimitedInt::add(UnlimitedInt::mul(num1, den2), UnlimitedInt::mul(num2, den1));
    UnlimitedInt* resultDen = UnlimitedInt::mul(den1, den2);
    UnlimitedInt* g = gcd(resultNum, resultDen);

    resultNum = UnlimitedInt::div(resultNum, g);
    resultDen = UnlimitedInt::div(resultDen, g);

    return new UnlimitedRational(resultNum, resultDen);
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    // Calculate the numerator and denominator for the result
    UnlimitedInt* resultNum = UnlimitedInt::sub(UnlimitedInt::mul(num1, den2), UnlimitedInt::mul(num2, den1));
    UnlimitedInt* resultDen = UnlimitedInt::mul(den1, den2);

    UnlimitedInt* g = gcd(resultNum, resultDen);

    resultNum = UnlimitedInt::div(resultNum, g);
    resultDen = UnlimitedInt::div(resultDen, g);
    return new UnlimitedRational(resultNum, resultDen);
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    // Calculate the numerator and denominator for the result
    UnlimitedInt* resultNum = UnlimitedInt::mul(num1, num2);
    UnlimitedInt* resultDen = UnlimitedInt::mul(den1, den2);

    UnlimitedInt* g = gcd(resultNum, resultDen);

    resultNum = UnlimitedInt::div(resultNum, g);
    resultDen = UnlimitedInt::div(resultDen, g);
    return new UnlimitedRational(resultNum, resultDen);
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    // Calculate the numerator and denominator for the result
    UnlimitedInt* resultNum = UnlimitedInt::mul(num1, den2);
    UnlimitedInt* resultDen = UnlimitedInt::mul(den1, num2);
    UnlimitedInt* g = gcd(resultNum, resultDen);

    resultNum = UnlimitedInt::div(resultNum, g);
    resultDen = UnlimitedInt::div(resultDen, g);
    return new UnlimitedRational(resultNum, resultDen);
}
