#include "HDF5Writer.hh"

#include "H5Cpp.h"


namespace {
  // concrete functions used in template specialization
  H5::CompType get_cluster_type();
  h5::Cluster get_empty_cluster();

  H5::CompType get_track_type();
  h5::Track get_empty_track();

  H5::EnumType get_bool_type();
}

namespace h5 {

  // actual template specializations
  template<>
  H5::DataType get_type<float>() {
    return H5::PredType::NATIVE_FLOAT;
  }
  template<>
  H5::DataType get_type<double>() {
    return H5::PredType::NATIVE_DOUBLE;
  }
  template<>
  H5::DataType get_type<bool>() {
    return get_bool_type();
  }

  template<>
  H5::DataType get_type<Cluster>() {
    return get_cluster_type();
  }
  template<>
  Cluster get_empty<Cluster>() {
    return get_empty_cluster();
  }

  template<>
  H5::DataType get_type<Track>() {
    return get_track_type();
  }
  template<>
  Track get_empty<Track>() {
    return get_empty_track();
  }

  // packing utility
  H5::DataType packed(H5::DataType in) {
    // TODO: Figure out why a normal copy constructor doesn't work here.
    //       The normal one seems to create shallow copies.
    auto out = H5::CompType(H5Tcopy(in.getId()));
    out.pack();
    return out;
  }

}

namespace {
  H5::CompType get_cluster_type() {
    auto ftype = h5::get_type<h5::outfloat_t>();
    auto btype = h5::get_type<bool>();
    H5::CompType type(sizeof(h5::Cluster));
#define INSERT(name, intype)                                      \
    type.insertMember(#name, offsetof(h5::Cluster, name), intype)
    INSERT(pt, ftype);
    INSERT(deta, ftype);
    INSERT(dphi, ftype);
    INSERT(energy, ftype);
    INSERT(mask, btype);
    INSERT(weight, ftype);
#undef INSERT
    return type;
  }
  h5::Cluster get_empty_cluster() {
    h5::Cluster cl;
    cl.pt = 0;
    cl.deta = 0;
    cl.dphi = 0;
    cl.energy = 0;
    cl.mask = true;
    cl.weight = 0;
    return cl;
  }


  H5::CompType get_track_type() {
    auto ftype = h5::get_type<h5::outfloat_t>();
    auto btype = h5::get_type<bool>();
    H5::CompType type(sizeof(h5::Track));
#define INSERT(name, intype)                                      \
    type.insertMember(#name, offsetof(h5::Track, name), intype)
    INSERT(pt, ftype);
    INSERT(deta, ftype);
    INSERT(dphi, ftype);
    INSERT(mask, btype);
    INSERT(weight, ftype);
#undef INSERT
    return type;
  }
  h5::Track get_empty_track() {
    h5::Track cl;
    cl.pt = 0;
    cl.deta = 0;
    cl.dphi = 0;
    cl.mask = true;
    cl.weight = 0;
    return cl;
  }

  H5::EnumType get_bool_type() {
    bool TRUE = true;
    bool FALSE = false;
    H5::EnumType btype(sizeof(bool));
    btype.insert("TRUE", &TRUE);
    btype.insert("FALSE", &FALSE);
    return btype;
  }

}
