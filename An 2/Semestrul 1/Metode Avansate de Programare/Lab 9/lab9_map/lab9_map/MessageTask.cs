namespace lab9_map;


public class MessageTask : Task
{
    public string Message { get; set; }
    public string From { get; set; }
    public string To { get; set; }
    public DateTime Date { get; set; }

    private static readonly string dateFormat = "yyyy-MM-dd HH:mm";

    public MessageTask(string id, string description, string message, string from, string to, DateTime date)
        : base(id, description)
    {
        Message = message;
        From = from;
        To = to;
        Date = date;
    }

    public override string ToString()
    {
        return $"id={Id} | description={Description} | message={Message} | from={From} | to={To} | date={Date.ToString(dateFormat)}";
    }

    public override void Execute()
    {
        Console.WriteLine($"{Date.ToString(dateFormat)}: {Message}");
    }
}
