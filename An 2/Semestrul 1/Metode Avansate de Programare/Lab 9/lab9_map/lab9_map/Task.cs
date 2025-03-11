namespace lab9_map;

public abstract class Task
{
    public string Id { get; set; }
    public string Description { get; set; }

    public Task(string id, string description)
    {
        Id = id;
        Description = description;
    }

    public override string ToString()
    {
        return $"Task{{id='{Id}', description='{Description}'}}";
    }

    public override bool Equals(object obj)
    {
        var task = obj as Task;
        return task != null && Id == task.Id && Description == task.Description;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Id, Description);
    }

    public abstract void Execute();
}