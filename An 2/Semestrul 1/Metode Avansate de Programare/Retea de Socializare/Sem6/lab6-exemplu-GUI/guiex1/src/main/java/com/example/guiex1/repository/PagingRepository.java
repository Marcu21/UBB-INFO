package com.example.guiex1.repository;


import com.example.guiex1.domain.Entity;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;

public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {

    Page<E> findAllByUserIdOnPage(Long userId, Pageable pageable);
    Page<E> findAllOnPage(Pageable pageable);
}
