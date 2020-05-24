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
    }
}