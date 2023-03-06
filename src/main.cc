// Markov Decision Process 
// DeepMind x UCL RL Lecture Series - MDPs and Dynamic Programming [3/13]
// https://www.youtube.com/watch?v=zSOMeug_i_M&list=PLqYmG7hTraZDVH599EItlEWsUOsJbAodm&index=3&ab_channel=DeepMind
// 
// tuple of (S, A, p, Y)
// S is the set of all Possible States
// A is the set of all Possible Actions 
// p(s', r| s, a) is the joint probability of a reward r and the next state s' given a state s and action a
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
mdp_t (all_states_t,all_actions_t, probability_kernel_t, reward_t, discount_t) ->
mdp_t <all_states_t,all_actions_t, probability_kernel_t, reward_t, discount_t>;

// returns a value state that is the same size as the states. 

template<class S, class A, class D, class R, class y = float>
auto i_policy_evaluation (mdp_t<S,A,D,R,y> && mdp) {


    return 0;
}

// example 4.1
#include <array>
#include <tuple>
#include <limits>
#include <iostream>

template<class T>
using state_space_t = std::array<std::array<T, 4>, 4>;

void grid_world_1 () {
    enum class action : int {up, down, right, left};
    std::array<action,4> actions {action::up, action::down, action::right, action::left};

    using states_t  = state_space_t<float>;
    using reward_t  = states_t;
    using actions_t = std::array<std::tuple<action, float>, 4>;
    using policy_t  = state_space_t<actions_t>;

    // Vk for the random policy
    states_t state_values {};
    states_t previous {};

    auto loop = [](auto& state, auto function){
        for(auto i = 0; i < state.size() ; i++) {
            for(auto j = 0; j < state[i].size(); j++) {
                function(state, i, j);
            }
        }
    };

    auto print = [&](auto const& state){
        std::cout << "\nVk :\n";
        loop(state, [](auto&s, auto i, auto j){ 
            std::cout << s[i][j]<< " ";
            if (j == 3 and (not(i == 3))) std::cout << "\n";
        });
        std::cout << std::endl;
    };

    int matches = 0;
    // pi (a | s) why is this constant in the book ? and equally distributed amongst all actions
    float state_choice = .25f;
    // p(s', r| s, a) why is this constant in the book
    float joint_prob_r_sprime = 1.f;
    // constant reward and discount
    float reward = -1.f, discount = 1.f;

    // create helper functions
    auto is_at_terminal_state = [](int i, int j){
        return (i == 0 and j == 0) or (i == 3 and j == 3);
    };

    auto is_passed_boundry = [](int i, int j){
        return (i < 0 or i > 3) or (j < 0 or j > 3);
    };

    auto next_move = [&](int i, int j, action a) {
        switch(a){
            case action::up:
              if (is_passed_boundry(i + 1, j)) return std::tuple{i, j};
                else return std::tuple{i + 1, j};
            case action::down:
                if (is_passed_boundry(i - 1, j)) return std::tuple{i, j};
                else return std::tuple{i - 1, j};
            case action::right:
             if (is_passed_boundry(i, j+ 1)) return std::tuple{i, j};
                else return std::tuple{i, j + 1};
            break; 
            case action::left:
                if (is_passed_boundry(i, j - 1)) return std::tuple{i, j};
                else return std::tuple{i, j - 1};
            break; 
            default:{ return std::tuple{0,0}; }
        }
    };

    auto are_equal = [](float a, float b){
        return std::abs(a-b) < std::numeric_limits<float>::epsilon();
    };
   
    int k = 0;
    // scan over set and update policies till convergence
    while (k < 10){
        std::cout << "\nk = " << k << "\n";
        // function that returns the state value function of a givin state for each each possible action it can take.
        previous = state_values;

        auto action_value = [&](auto& s, auto i, auto j, action a) {
            if (is_at_terminal_state(i, j)) return 0.f;
            auto[i2, j2] = next_move(i, j, a);
            return state_choice * joint_prob_r_sprime * (reward + (discount * s[i2][j2]));
        }; 

        print(state_values);
        loop(previous, [&](auto& s, auto i, auto j) {
            auto sum = 0.f;
            for(auto a : actions) { 
                sum += action_value(s,i,j,a); 
            }
            state_values[i][j] = sum; 
        });
      

        k++;
    }




    // auto value = i_policy_evaluation (mdp_t {
    //             states_t{},
    //             actions_t{},
    //             [reward_states = reward_t{}] ( ) mutable {
    //             },
    //             [](){},
    //             discount
    // });
}


int main () {
    grid_world_1();
    return 0;
}