#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}

  virtual std::string toString() const = 0;

  virtual long evaluate() const = 0;

  virtual ~Expression() {}  // gurantee dinamic dispatch
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}

  std::string toString() const {
    std::stringstream strstream;
    std::string result;
    strstream << num;
    result = strstream.str();

    return result;
  }

  long evaluate() const { return num; }

  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}

  std::string toString() const {
    std::string l_num = lhs->toString();
    std::string r_num = rhs->toString();

    std::stringstream strstream;
    std::string result;
    strstream << "(" << l_num << " + " << r_num << ")";
    result = strstream.str();

    return result;
  }

  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}

  std::string toString() const {
    std::string l_num = lhs->toString();
    std::string r_num = rhs->toString();

    std::stringstream strstream;
    std::string result;
    strstream << "(" << l_num << " - " << r_num << ")";
    result = strstream.str();

    return result;
  }

  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }

  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}

  std::string toString() const {
    std::string l_num = lhs->toString();
    std::string r_num = rhs->toString();

    std::stringstream strstream;
    std::string result;
    strstream << "(" << l_num << " * " << r_num << ")";
    result = strstream.str();

    return result;
  }

  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }

  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}

  std::string toString() const {
    std::string l_num = lhs->toString();
    std::string r_num = rhs->toString();

    std::stringstream strstream;
    std::string result;
    strstream << "(" << l_num << " / " << r_num << ")";
    result = strstream.str();

    return result;
  }

  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }

  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
