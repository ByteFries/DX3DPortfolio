#pragma once
class CalculatorLinearBasic : public PhysicalCalculator
{
public:
	CalculatorLinearBasic() {}
	~CalculatorLinearBasic() {}

	void Calculate(PhysicalObject* target) override;

private:
};