public class InmultireExpresie extends ComplexExpression {
    public InmultireExpresie(NumarComplex[] args) {
        super(Operation.MULTIPLICATION, args);
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
        return c1.inmultire(c2);
    }
}