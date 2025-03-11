namespace lab9_map;

public interface Factory
{
    Container CreateContainer(Strategy strategy);
}
