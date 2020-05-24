using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Linq.Expressions;

namespace ExpertSystem
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var facts = CreateAllRangeFacts();

            var mainExpressionList = MakeExpressionTreesAndSetUsesFacts(facts);

            var initialFacts = new List<char> {'D', 'K'};
            facts = FilterAndCheckFacts(facts, initialFacts);
            InitFacts(facts, initialFacts);

            var queries = new List<char> {'A', 'B', 'C', 'D', 'K'};
            CheckQueries(facts, queries);

            foreach (var query in queries)
            {
                PrintAnswer(EvaluateQuery(mainExpressionList, facts.FirstOrDefault(f => f.Name == query)));
            }
        }

        private static void PrintAnswer(State state)
        {
            Console.WriteLine(state);
        }

        private static List<Fact> CreateAllRangeFacts()
        {
            var facts = new List<Fact>();
            for (var i = 'A'; i <= 'Z'; i++)
            {
                facts.Add(new Fact {Name = i});
            }

            return facts;
        }

        private static List<ExpressionOperation> MakeExpressionTreesAndSetUsesFacts(List<Fact> facts)
        {
            return new List<ExpressionOperation>
            {
                new ExpressionOperation
                {
                    ExpressionLeft = new ExpressionOperation
                    {
                        ExpressionLeft = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'A')),
                        Operation = BinaryOperation.And,
                        ExpressionRight = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'B'))
                    },
                    Operation = BinaryOperation.Implies,
                    ExpressionRight = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'C'))
                },
                new ExpressionOperation
                {
                    ExpressionLeft = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'D')),
                    Operation = BinaryOperation.Implies,
                    ExpressionRight = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'A')),
                },
                new ExpressionOperation
                {
                    ExpressionLeft = new ExpressionOperation
                    {
                        ExpressionLeft = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'K')),
                        Operation = BinaryOperation.Not
                    },
                    Operation = BinaryOperation.Implies,
                    ExpressionRight = new ExpressionFact(facts.FirstOrDefault(f => f.Name == 'B')),
                }
            };
        }

        private static void InitFacts(List<Fact> facts, List<char> initialFacts)
        {
            foreach (var fact in facts.Where(f => initialFacts.Contains(f.Name)))
            {
                fact.State = State.True;
            }
        }

        private static List<Fact> FilterAndCheckFacts(List<Fact> facts, List<char> initialFacts)
        {
            facts = facts.Where(f => f.IsSet).ToList();

            if (initialFacts.All(i => !facts.Select(f => f.Name).ToList().Contains(i)))
            {
                throw new Exception();
            }

            return facts;
        }

        private static void CheckQueries(List<Fact> facts, List<char> queries)
        {
            if (queries.All(q => !facts.Select(f => f.Name).ToList().Contains(q)))
            {
                throw new Exception();
            }
        }

        private static State EvaluateQuery(List<ExpressionOperation> mainExpressionList, Fact fact)
        {
            foreach (var expressionOperation in mainExpressionList)
            {
                if (fact.State == State.True)
                {
                    return fact.State;
                }

                if (expressionOperation.Operation == BinaryOperation.Implies && expressionOperation.ExpressionRight.Contains(fact))
                {
                    expressionOperation.ExpressionRight.EvaluateFactsInsideExpression(
                        EvaluateExpression(mainExpressionList, expressionOperation.ExpressionLeft));
//                    expressionOperation.ExpressionRight.EvaluateFactsInsideExpression(
//                        EvaluateExpression(mainExpressionList, expressionOperation.ExpressionLeft));
                }
            }

            return fact.State;
        }

        private static State EvaluateExpression(List<ExpressionOperation> mainExpressionList, Expression expression)
        {
            switch (expression)
            {
                case ExpressionOperation expressionOperation:
                    return ExpressionOperation.EvaluateState(
                        EvaluateExpression(mainExpressionList, expressionOperation.ExpressionLeft),
                        expressionOperation.Operation,
                        EvaluateExpression(mainExpressionList, expressionOperation.ExpressionRight));
                case ExpressionFact expressionFact:
                    return EvaluateQuery(mainExpressionList, expressionFact.Fact);
                default:
                    return State.False;
            }
        }
    }
}