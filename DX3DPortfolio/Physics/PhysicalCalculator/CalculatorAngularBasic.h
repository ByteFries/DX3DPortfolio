#pragma once
class PhysicalObject;

class CalculatorAngularBasic : public PhysicalCalculator
{
public:
	CalculatorAngularBasic() {}
	void Calculate(PhysicalObject* target) override;
private:
};