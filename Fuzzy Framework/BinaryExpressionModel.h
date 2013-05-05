#ifndef BINARYEXPRESSIONMODEL_H
#define BINARYEXPRESSIONMODEL_H

namespace core
{
	template <class T>
	class BinaryExpressionModel: public BinaryExpression<T>, public Expression<T>
	{
	public:
		BinaryExpressionModel() {};
		BinaryExpressionModel(BinaryExpression<T>* operateur, Expression<T>* left, Expression<T>* right): operateur(operateur), left(left), right(right) {};
		virtual ~BinaryExpressionModel() {};
		
		virtual T Evaluate() const;
		virtual T Evaluate(Expression<T>*, Expression<T>*) const;

		BinaryExpression<T>* GetOpe();
		void SetOpe(BinaryExpression<T>*);

	private:
		BinaryExpression<T>* operateur;
		Expression<T>* left;
		Expression<T>* right;
	};

	template <class T>
	T BinaryExpressionModel<T>::Evaluate(Expression<T>* l, Expression<T>* r) const
	{
		if (operateur == NULL)
			throw new NullExpressionException("operateur null");

		return operateur->Evaluate(l, r);
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
		return operateur;
	}
	
	template <class T>
	void BinaryExpressionModel<T>::SetOpe(BinaryExpression<T>* o)
	{
		operateur = o;
	}
}

#endif
