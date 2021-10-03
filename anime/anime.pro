QT       += core gui network widgets charts

CONFIG += c++17

TEMPLATE = app
DESTDIR  = /build
INCLUDEPATH += Q:\git\episodes\anime\oneapi-tbb-2021.3.0-win\oneapi-tbb-2021.3.0\include

LIBS += -L"$$_PRO_FILE_PWD_"
LIBS += -ltbb
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animatedcursor.cpp \
    dialog.cpp \
    form.cpp \
    main.cpp \
    sortcombobox.cpp \
    tablesortmodel.cpp \
    widget.cpp

HEADERS += \
    DataTypes.h \
    animatedcursor.h \
    dialog.h \
    form.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/blocked_range.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/blocked_range2d.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/blocked_range3d.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/blocked_rangeNd.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/cache_aligned_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/combinable.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_hash_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_lru_cache.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_priority_queue.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_queue.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_set.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_unordered_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_unordered_set.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/concurrent_vector.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_aggregator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_aligned_space.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_allocator_traits.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_assert.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_concurrent_queue_base.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_concurrent_skip_list.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_concurrent_unordered_base.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_config.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_containers_helpers.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_exception.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_body_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_cache_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_indexer_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_item_buffer_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_join_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_node_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_node_set_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_nodes_deduction.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_tagged_buffer_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_trace_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_flow_graph_types_impl.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_hash_compare.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_machine.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_mutex_common.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_namespace_injection.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_node_handle.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_pipeline_filters.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_pipeline_filters_deduction.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_range_common.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_rtm_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_rtm_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_scoped_lock.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_segment_table.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_small_object_pool.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_string_resource.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_task.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_template_helpers.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_utils.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/detail/_waitable_atomic.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/enumerable_thread_specific.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/flow_graph.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/flow_graph_abstractions.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/global_control.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/info.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/memory_pool.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/null_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/null_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_for.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_for_each.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_invoke.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_pipeline.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_reduce.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_scan.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/parallel_sort.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/partitioner.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/profiling.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/queuing_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/queuing_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/scalable_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/spin_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/spin_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/task.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/task_arena.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/task_group.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/task_scheduler_observer.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/tbb_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/tbbmalloc_proxy.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/tick_count.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/oneapi/tbb/version.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/blocked_range.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/blocked_range2d.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/blocked_range3d.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/blocked_rangeNd.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/cache_aligned_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/combinable.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_hash_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_lru_cache.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_priority_queue.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_queue.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_set.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_unordered_map.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_unordered_set.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/concurrent_vector.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/enumerable_thread_specific.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/flow_graph.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/flow_graph_abstractions.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/global_control.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/info.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/memory_pool.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/null_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/null_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_for.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_for_each.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_invoke.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_pipeline.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_reduce.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_scan.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/parallel_sort.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/partitioner.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/profiling.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/queuing_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/queuing_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/scalable_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/spin_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/spin_rw_mutex.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/task.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/task_arena.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/task_group.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/task_scheduler_observer.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/tbb.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/tbb_allocator.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/tbbmalloc_proxy.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/tick_count.h \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/include/tbb/version.h \
    sortcombobox.h \
    tablesortmodel.h \
    widget.h

FORMS += \
    dialog.ui \
    form.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Designbolts-Thin-Download-Server-File-Download.ico \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/.gitattributes \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/.gitignore \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/LICENSE.txt \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/README.md \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/env/vars.bat \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/cmake/tbb/TBBConfig.cmake \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/cmake/tbb/TBBConfigVersion.cmake \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbb.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbb12.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbb12_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbb_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind_2_0.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind_2_0_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind_2_4.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind_2_4_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbbind_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbmalloc.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbmalloc_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbmalloc_proxy.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14/tbbmalloc_proxy_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbb.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbb12.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbb12_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbb_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbbmalloc.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbbmalloc_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbbmalloc_proxy.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/ia32/vc14_uwp/tbbmalloc_proxy_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbb.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbb12.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbb12_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbb_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind_2_0.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind_2_0_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind_2_4.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind_2_4_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbbind_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbmalloc.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbmalloc_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbmalloc_proxy.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14/tbbmalloc_proxy_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbb.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbb12.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbb12_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbb_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbbmalloc.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbbmalloc_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbbmalloc_proxy.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/lib/intel64/vc14_uwp/tbbmalloc_proxy_debug.lib \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbb.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbb12.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbb12.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbb12_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbb12_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_0.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_0.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_0_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_0_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_4.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_4.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_4_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_2_4_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbbind_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_proxy.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_proxy.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_proxy_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14/tbbmalloc_proxy_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbb.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbb12.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbb12.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbb12_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbb12_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_proxy.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_proxy.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_proxy_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/ia32/vc14_uwp/tbbmalloc_proxy_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbb.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbb12.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbb12.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbb12_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbb12_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_0.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_0.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_0_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_0_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_4.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_4.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_4_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_2_4_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbbind_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_proxy.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_proxy.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_proxy_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14/tbbmalloc_proxy_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbb.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbb12.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbb12.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbb12_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbb12_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc.def \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_proxy.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_proxy.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_proxy_debug.dll \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/redist/intel64/vc14_uwp/tbbmalloc_proxy_debug.pdb \
    oneapi-tbb-2021.3.0-win/oneapi-tbb-2021.3.0/third-party-programs.txt

RESOURCES += \
    rc.qrc
