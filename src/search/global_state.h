#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "state_id.h"

#include "algorithms/int_packer.h"

class State;
class StateRegistry;

using PackedStateBin = int_packer::IntPacker::Bin;

// Alberto Pozanco
class GP{
public:
    std::vector <std::string> atoms;
    double probability;
};

// For documentation on classes relevant to storing and working with registered
// states see the file state_registry.h.
class GlobalState {
    friend class StateRegistry;
    template<typename Entry>
    friend class PerStateInformation;
    template<typename>
    friend class PerStateArray;
    friend class PerStateBitset;

    // Values for vars are maintained in a packed state and accessed on demand.
    const PackedStateBin *buffer;

    // registry isn't a reference because we want to support operator=
    const StateRegistry *registry;
    StateID id;

    // Only used by the state registry.
    GlobalState(
        const PackedStateBin *buffer, const StateRegistry &registry, StateID id);

    const PackedStateBin *get_packed_buffer() const {
        return buffer;
    }

    const StateRegistry &get_registry() const {
        return *registry;
    }
public:
    ~GlobalState() = default;

    StateID get_id() const {
        return id;
    }

    int operator[](int var) const;

    State unpack() const;

    void dump_pddl() const;
    void dump_fdr() const;
    std::vector<std::string> return_pddl() const;
};


#endif