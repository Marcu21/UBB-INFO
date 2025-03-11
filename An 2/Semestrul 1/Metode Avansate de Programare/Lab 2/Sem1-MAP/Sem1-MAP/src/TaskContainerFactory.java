public class TaskContainerFactory implements Factory{
    private static TaskContainerFactory instance = new TaskContainerFactory();

    private TaskContainerFactory() {}

    public static TaskContainerFactory getInstance() {
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        switch(strategy){
            case FIFO:
                return new T_QueueContainer();
            case LIFO:
                return new StackContainer();
            default: return null;
        }
    }
}
