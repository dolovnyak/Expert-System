namespace ExpertSystem
{
    public abstract class Expression
    {
        public abstract bool Contains(Fact fact);

        public abstract void EvaluateFactsInsideExpression(State state);
    }
}