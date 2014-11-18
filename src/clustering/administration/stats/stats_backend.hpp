// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef CLUSTERING_ADMINISTRATION_STATS_STATS_BACKEND_HPP_
#define CLUSTERING_ADMINISTRATION_STATS_STATS_BACKEND_HPP_

#include <string>
#include <vector>

#include "errors.hpp"
#include <boost/shared_ptr.hpp>

#include "rdb_protocol/artificial_table/backend.hpp"
#include "clustering/administration/metadata.hpp"
#include "concurrency/watchable.hpp"

class stats_artificial_table_backend_t :
    public artificial_table_backend_t
{
public:
    stats_artificial_table_backend_t(
        const clone_ptr_t<watchable_t<change_tracking_map_t<peer_id_t,
            cluster_directory_metadata_t> > >
                &directory_view,
        server_name_client_t *_name_client);

    std::string get_primary_key_name();

    bool read_all_rows_as_vector(signal_t *interruptor,
                                 std::vector<ql::datum_t> *rows_out,
                                 std::string *error_out);

    bool read_row(ql::datum_t primary_key,
                  signal_t *interruptor,
                  ql::datum_t *row_out,
                  std::string *error_out);

    bool write_row(ql::datum_t primary_key,
                   bool pkey_was_autogenerated,
                   ql::datum_t *new_value_inout,
                   signal_t *interruptor,
                   std::string *error_out);

private:
    clone_ptr_t<watchable_t<change_tracking_map_t<peer_id_t,
        cluster_directory_metadata_t> > > directory_view;
    server_name_client_t *name_client;
};

#endif /* CLUSTERING_ADMINISTRATION_STATS_STATS_BACKEND_HPP_ */