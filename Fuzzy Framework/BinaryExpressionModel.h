#ifndef BINARYEXPRESSIONMODEL_H
#define BINARYEXPRESSIONMODEL_H

namespace core
{
	template <class T>
	class BinaryExpressionModel: public BinaryExpression<T>, public Expression<T>
	{
	public:
		BinaryExpressionModel() {};
		BinaryExpressionModel(BinaryExpression<T>* ope, Expression<T>* left, Expression<T>* right): ope(ope), left(left), right(right) {};
		virtual ~BinaryExpressionModel() {};
		
		virtual T Evaluate() const;
		virtual T Evaluate(Expression<T>*, Expression<T>*) const;

		BinaryExpression<T>* GetOpe();
		void SetOpe(BinaryExpression<T>*);

	private:
		BinaryExpression<T>* ope;
		Expression<T>* left;
		Expression<T>* right;
	};

	template <class T>
	T BinaryExpressionModel<T>::Evaluate(Expression<T>* l, Expression<T>* r) const
	{
		if (ope == NULL)
			throw new NullExpressionException("ope null");

		return ope->Evaluate(l, r);
	}

	template <class T>
	T BinaryExpressionModel<T>::Evaluate() const
	{
		if (left == NULL)
			throw new NullExpressionException("left null");

		if (right == NULL)
			throw new NullExpressionException("right null");

		return Evaluate(left, right);
	}

	template <class T>
	BinaryExpression<T>* BinaryExpressionModel<T>::GetOpe()
	{
		return ope;
	}
	
	template <class T>
	void BinaryExpressionModel<T>::SetOpe(BinaryExpression<T>* _ope)
	{
		ope = _ope;
	}
}

#endif
