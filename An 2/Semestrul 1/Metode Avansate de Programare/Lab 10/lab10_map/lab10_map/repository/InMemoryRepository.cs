using lab10_map.domain;

namespace lab10_map.repository;

public class InMemoryRepository<E,ID> : IRepository<E, ID> where E : Entity<ID>
{
    Dictionary<ID,E> Dictionary = new ();
    
    public E? FindOne(ID id)
    {
        return Dictionary.ContainsKey(id) ? Dictionary[id] : default;
    }

    public IEnumerable<E> FindAll()
    {
        return Dictionary.Values;
    }

    public virtual E? Save(E entity)
    {
        return Dictionary.TryAdd(entity.Id, entity) ? entity : null;
    }

    public virtual E? Delete(ID id)
    {
        Dictionary.Remove(id, out E? entity);
        return entity;
    }

    public virtual E? Update(E entity)
    {
        if(!Dictionary.ContainsKey(entity.Id))
            return null;
        Dictionary[entity.Id] = entity;
        return entity;
    }
}