using System;

namespace ExpertSystem
{
    public class ExpressionOperation : Expression
    {
        public BinaryOperation Operation { get; set; }
        
        public Expression ExpressionLeft { get; set; }
        
        public Expression ExpressionRight { get; set; }

        public static State EvaluateState(State state1, BinaryOperation binaryOperation, State state2)
        {
            switch (binaryOperation)
            {
                case BinaryOperation.Not:
                    switch (state1)
                    {
                        case State.False:
                            return State.True;
                        case State.True:
                            return State.False;
                    } 
                    return State.Undetermined;
                case BinaryOperation.And:
                    if (state1 == State.True && state2 == State.True)
                    {
                        return State.True;
                    }
                    return State.False;
            }

            throw new Exception();
        }

        public override bool Contains(Fact fact)
        {
            return ExpressionLeft.Contains(fact) || ExpressionRight.Contains(fact);
        }

        public override void EvaluateFactsInsideExpression(State state)
        {
            ExpressionLeft.EvaluateFactsInsideExpression(state);
            //TODO
            ExpressionRight.EvaluateFactsInsideExpression(state);
        }
    }
}