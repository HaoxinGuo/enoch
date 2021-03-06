/***************************************************************************
 *   Copyright (C) 2005 by David de Koning                                 *
 *   david@dekoning.ca                                                     *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/
#ifndef CONSTRAINT
#define CONSTRAINT

class Constraint {
public:
  Constraint(bool type) { this->type = type; };

  static const bool FORCE = false, DISP = true;

  bool getType() { return type; };

protected:
  bool type;
};


class StaticConstraint: public Constraint {
public:
  StaticConstraint(bool type, double value);

  double getValue() { return value; };
 
protected:
  double value;
};


class DynamicConstraint: public Constraint {
public:
  DynamicConstraint(bool type) : Constraint(type){};
  virtual double getValue(double t);
  virtual double getdValue(double t, double dt);
};


class ConstantDynamicConstraint: public DynamicConstraint {
public:
  ConstantDynamicConstraint(bool type, double To, double value);
  double getValue(double t);
  double getdValue(double t, double dt);

protected:
  double value;
  double startTime;
};

class SinusoidalConstraint: public DynamicConstraint {
public:
  SinusoidalConstraint(bool type, double A, double w, double phi);
  double getValue(double t);
  double getdValue(double t, double dt);

protected:
  double A, w, phi;
};
#endif 
