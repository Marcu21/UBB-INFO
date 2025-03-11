
using lab9_map;

class Program
{
    static void Main(string[] args)
    {
        MessageTask[] tasks = new MessageTask[5];
        tasks[0]=new MessageTask("1", "mail", "cv", "arthur", "employer", DateTime.Now);
        tasks[1]=new MessageTask("2", "mail","resignation letter", "steffen", "employer", DateTime.Now);
        tasks[2]=new MessageTask("3", "mail", "cv", "steve", "employer", DateTime.Now);
        tasks[3]=new MessageTask("4", "mail", "cv", "mary", "employer", DateTime.Now);
        tasks[4]=new MessageTask("5", "mail", "cv", "margaret", "employer", DateTime.Now);
        
        foreach (MessageTask task in tasks)
        {
            Console.WriteLine(task);
        }
        
        Strategy strategy;
        try
        {
            strategy = Enum.Parse<Strategy>(args[0], ignoreCase: true);
        }
        catch (ArgumentException)
        {
            Console.WriteLine("Strategie invalida!");
            return;
        }

        TaskRunner strategyTaskRunner = new StrategyTaskRunner(strategy);
        
        foreach (MessageTask task in tasks)
        {
            strategyTaskRunner.AddTask(task);
        }
        Console.WriteLine("Strategy Task Runner: " + strategy);
        strategyTaskRunner.ExecuteAll();
        
        
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        foreach (MessageTask task in tasks)
        {
            printerTaskRunner.AddTask(task);
        }
        Console.WriteLine("Printer Task Runner: " + strategy);
        printerTaskRunner.ExecuteAll();
    }
}