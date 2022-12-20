// Markov Decision Process 
// DeepMind x UCL RL Lecture Series - MDPs and Dynamic Programming [3/13]
// https://www.youtube.com/watch?v=zSOMeug_i_M&list=PLqYmG7hTraZDVH599EItlEWsUOsJbAodm&index=3&ab_channel=DeepMind
// 
// tuple of (S, A, p, Y)
// S is the set of all Possible States
// A is the set of all Possible Actions 
// p (r, s' | s, a) is the joint probability of a reward r and the next state s' given a state s and action a
// Y is btwn [0,1], is a discount factor that trades off later rewards to ealier ones  

template<class all_states_t, class all_actions_t, class probability_kernel_t, class reward_t, class discount_t = float>
struct mdp_t {
    all_states_t         states;
    all_actions_t        actions;
    probability_kernel_t dynamics;
    reward_t             reward;
    discount_t           discount;
};


// Deductuction guide 
template<class all_states_t, class all_actions_t, class probability_kernel_t, class reward_t>
mdp_t (all_states_t,all_actions_t,probability_kernel_t, reward_t) ->
mdp_t <all_states_t,all_actions_t,probability_kernel_t, reward_t>;

// Deductuction guide 
template<class all_states_t, class all_actions_t, class probability_kernel_t, class reward_t, class discount_t>
mdp_t (all_states_t,all_actions_t,probability_kernel_t, reward_t, discount_t) ->
mdp_t <all_states_t,all_actions_t,probability_kernel_t, reward_t, discount_t>;

// returns a value state that is the same size as the states. 
template <class MDP>
auto i_policy_evaluation (MDP && mdp) {
    return 0;
}

// example 4.1
#include <array>
template<class T>
using state_space_t = std::array<std::array<T, 4>,4>;

void grid_world_1 () {
    enum class action : uint8_t {up, down, right, left};

    using states_t  = state_space_t<float>;
    using reward_t  = states_t;
    using actions_t = std::array<action,4>;
    using policy_t  = state_space_t<actions_t>;
    
    float discount = 1.f;

    auto value = i_policy_evaluation (mdp_t {
                states_t{},
                actions_t{},
                [](){},
                [](){},
                discount
    });
}


int main () {
    
    return 0;
}