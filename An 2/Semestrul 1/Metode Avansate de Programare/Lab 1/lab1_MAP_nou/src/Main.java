public class Main {
    public static void main(String[] args) {
        try {
            NumarComplex result = ExpressionParser.evalueaza(args);
            System.out.println("Rezultat: " + result);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
