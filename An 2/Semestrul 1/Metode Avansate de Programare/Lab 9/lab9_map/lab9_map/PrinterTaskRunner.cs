namespace lab9_map;

public class PrinterTaskRunner : AbstractTaskRunner
{
    public PrinterTaskRunner(TaskRunner taskRunner) : base(taskRunner)
    {
    }
    
    private static readonly string formatter = "HH:mm";
    
    public void ExecuteOneTask()
    {
        base.ExecuteOneTask();
        Console.WriteLine($"Task executed at {DateTime.Now.ToString(formatter)}");
    }
}