public class AdaugareExpresie extends ComplexExpression {
    public AdaugareExpresie(NumarComplex[] args) {
        super(Operation.ADDITION, args);
    }

    @Override
    public NumarComplex execute() {
        NumarComplex result = args[0];
        for (int i = 1; i < args.length; i++) {
            result = executeOneOperation(result, args[i]);
        }
        return result;
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex c1, NumarComplex c2) {
        return c1.adunare(c2);
    }
}