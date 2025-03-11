public abstract class ComplexExpression {
    protected Operation operation;
    protected NumarComplex[] args;

    public ComplexExpression(Operation operation, NumarComplex[] args) {
        this.operation = operation;
        this.args = args;
    }

    public abstract NumarComplex execute();

    protected abstract NumarComplex executeOneOperation(NumarComplex c1, NumarComplex c2);
}
