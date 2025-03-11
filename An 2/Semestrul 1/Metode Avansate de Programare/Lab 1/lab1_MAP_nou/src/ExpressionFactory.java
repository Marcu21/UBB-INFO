public class ExpressionFactory {
    private static ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {}

    public static ExpressionFactory getInstance() {
        return instance;
    }

    public ComplexExpression createExpression(Operation operation, NumarComplex[] args) {
        switch (operation) {
            case ADDITION:
                return new AdaugareExpresie(args);
            case SUBSTRACTION:
                return new ScadereExpresie(args);
            case MULTIPLICATION:
                return new InmultireExpresie(args);
            case DIVISION:
                return new ImpartireExpresie(args);
            default:
                throw new IllegalArgumentException("Invalid operation");
        }
    }
}
