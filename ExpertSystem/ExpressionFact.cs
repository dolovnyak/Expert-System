namespace ExpertSystem
{
    public class ExpressionFact : Expression
    {
        public Fact Fact { get; set; }

        public ExpressionFact(Fact fact)
        {
            fact.IsSet = true;
            Fact = fact;
        }
        
        public override bool Contains(Fact fact)
        {
            return fact.Name == Fact.Name;
        }

        public override void EvaluateFactsInsideExpression(State state)
        {
            Fact.State = state;
        }
    }
}