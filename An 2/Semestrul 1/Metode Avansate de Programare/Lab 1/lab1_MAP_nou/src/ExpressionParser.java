public class ExpressionParser {
    public static NumarComplex evalueaza(String[] args) {
        if (args.length < 3 || args.length % 2 == 0) {
            throw new IllegalArgumentException("Expresie invalida!");
        }

        NumarComplex result = parseComplex(args[0]);
        if (result == null) {
            throw new IllegalArgumentException("Primul argument este invalid!");
        }

        for (int i = 1; i < args.length; i += 2) {
            String operator = args[i];
            NumarComplex nextOperand = parseComplex(args[i + 1]);
            if (nextOperand == null) {
                throw new IllegalArgumentException("Argumentul " + (i + 1) + " este invalid!");
            }

            NumarComplex[] operands = {result, nextOperand};

            switch (operator) {
                case "+":
                    result = ExpressionFactory.getInstance().createExpression(Operation.ADDITION, operands).execute();
                    break;
                case "-":
                    result = ExpressionFactory.getInstance().createExpression(Operation.SUBSTRACTION, operands).execute();
                    break;
                case "*":
                    result = ExpressionFactory.getInstance().createExpression(Operation.MULTIPLICATION, operands).execute();
                    break;
                case "/":
                    result = ExpressionFactory.getInstance().createExpression(Operation.DIVISION, operands).execute();
                    break;
                default:
                    throw new IllegalArgumentException("Operatorul " + operator + " este invalid!");
            }
        }
        return result;
    }

    private static NumarComplex parseComplex(String s) {
        s = s.replaceAll("\\s+", "");
        String[] parts = s.split("(?=[+-])", 2);
        if (parts.length < 2) {
            return null;
        }
        try {
            double re = Double.parseDouble(parts[0]);
            double im = Double.parseDouble(parts[1].replaceAll("i", ""));
            return new NumarComplex(re, im);
        } catch (Exception e) {
            return null;
        }
    }
}
