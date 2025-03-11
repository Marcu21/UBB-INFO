using lab10_map.domain;

namespace lab10_map.repository;


public interface IRepository<E, ID> where E : Entity<ID>
{
    E? FindOne(ID id);
    IEnumerable<E> FindAll();
    E? Save(E entity);
    E? Delete(ID id);
    E? Update(E entity);
}