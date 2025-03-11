public class StrategyTaskRunner implements TaskRunner{
    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        TaskContainerFactory factory=TaskContainerFactory.getInstance();
        container= factory.createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        Task t=container.remove();
        t.execute();
    }

    @Override
    public void executeAll() {
        while(hasTask()){
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
