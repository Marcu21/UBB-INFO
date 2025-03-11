import java.time.LocalDateTime;

public class Main {
    public static void main(String[] args) {
        MessageTask[] tasks = new MessageTask[5];
        tasks[0]=new MessageTask("mail", "1", "cv", "arthur", "employer", LocalDateTime.now());
        tasks[1]=new MessageTask("mail", "2", "resignation letter", "steffen", "employer", LocalDateTime.now());
        tasks[2]=new MessageTask("mail", "3", "cv", "steve", "employer", LocalDateTime.now());
        tasks[3]=new MessageTask("mail", "4", "cv", "mary", "employer", LocalDateTime.now());
        tasks[4]=new MessageTask("mail", "5", "cv", "margaret", "employer", LocalDateTime.now());

        /*for (MessageTask task : tasks) {
            System.out.println(task);
        }*/

        TaskRunner strategyTaskRunner=new StrategyTaskRunner(Strategy.valueOf(args[0]));
        for (MessageTask task : tasks) {
            strategyTaskRunner.addTask(task);
        }
        System.out.println("Strategy task runner");
        strategyTaskRunner.executeAll();


        TaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        for (MessageTask task : tasks) {
            delayTaskRunner.addTask(task);
        }
        System.out.println("Delay task runner");
        delayTaskRunner.executeAll();

        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        for (MessageTask task : tasks) {
            printerTaskRunner.addTask(task);
        }
        System.out.println("Printer task runner");
        printerTaskRunner.executeAll();

        System.out.println("Sorting tasks");
        int[] lista1 = {1, 4, 2, 3, 5};
        T_SortingTask sortingTask = new T_SortingTask("sortare", "1", lista1, SortStrategy.valueOf(args[1]));
        sortingTask.execute();

    }
}