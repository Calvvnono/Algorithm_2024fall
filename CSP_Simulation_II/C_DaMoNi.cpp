#include <bits/stdc++.h>
using namespace std;

// Define constants for card IDs
enum CardID {
    PY_JIAOYI = 0,
    GONGJI = 1,
    SHANBI = 2,
    HUIFU = 3,
    MINGXIAN = 4,
    FANJI = 5,
    DANMU = 6,
    YANBAO = 7,
    FENGYIN = 8
};

// Define team identifiers
enum Team {
    ZYF = 0, // Even-numbered players
    GPX = 1  // Odd-numbered players
};

// Player structure
struct Player {
    int id;
    Team team;
    int max_health;
    int current_health;
    int max_mana;
    int current_mana;
    bool alive;
    vector<int> hand;
};

// Function to sort hand based on priority
bool sort_hand(const int &a, const int &b) {
    // Basic cards: 0-4, Spell cards:5-8
    bool a_basic = (a >= 0 && a <=4);
    bool b_basic = (b >=0 && b <=4);
    if(a_basic && !b_basic) return true;
    if(!a_basic && b_basic) return false;
    if(a_basic && b_basic){
        return a < b;
    }
    // Both spell cards
    return a < b;
}

// Function to check if a team is defeated
bool is_team_defeated(const vector<Player> &players, Team team) {
    for(auto &p : players){
        if(p.team == team && p.alive){
            return false;
        }
    }
    return true;
}

// Function to get the lowest-numbered alive enemy
int get_lowest_alive_enemy(const vector<Player> &players, const Player &current_player) {
    int target = -1;
    for(auto &p : players){
        if(p.team != current_player.team && p.alive){
            if(target == -1 || p.id < target){
                target = p.id;
            }
        }
    }
    return target;
}

// Function to get all alive enemies
vector<int> get_all_alive_enemies(const vector<Player> &players, const Player &current_player) {
    vector<int> enemies;
    for(auto &p : players){
        if(p.team != current_player.team && p.alive){
            enemies.push_back(p.id);
        }
    }
    return enemies;
}

// Function to execute damage and handle death
void apply_damage(vector<Player> &players, int target_id, int damage) {
    if(target_id == -1) return;
    Player &target = players[target_id];
    if(!target.alive) return;
    target.current_health -= damage;
    if(target.current_health <= 0){
        target.current_health = 0;
        target.alive = false;
        target.hand.clear(); // Discard all hand cards
    }
}

// Function to apply healing
void apply_heal(vector<Player> &players, int target_id, int heal_amount) {
    if(target_id == -1) return;
    Player &target = players[target_id];
    if(!target.alive) return;
    target.current_health = min(target.current_health + heal_amount, target.max_health);
}

// Function to execute '封印' (Seal)
void execute_fengyin(vector<Player> &players, int caster_id) {
    for(auto &p : players){
        if(p.id != caster_id && p.alive){
            p.current_mana = 0;
        }
    }
}

// Function to execute '冥想' (Meditate)
void execute_mingxian(vector<Player> &players, int caster_id) {
    Player &caster = players[caster_id];
    if(!caster.alive) return;
    caster.current_mana += caster.max_mana;
}

// Function to execute '炎爆' (Flame Burst)
void execute_yanbao(vector<Player> &players, int caster_id) {
    Player &caster = players[caster_id];
    if(!caster.alive) return;
    int damage = caster.current_mana;
    caster.current_mana = 0;
    int target_id = get_lowest_alive_enemy(players, caster);
    apply_damage(players, target_id, damage);
}

// Function to execute '弹幕' (Barrages)
void execute_danmu(vector<Player> &players, int caster_id) {
    vector<int> enemies = get_all_alive_enemies(players, players[caster_id]);
    for(auto enemy_id : enemies){
        apply_damage(players, enemy_id, 1);
    }
}

// Function to execute '反击' (Counter) - handled as a reaction, so no need here

// Function to execute '攻击' (Attack)
void execute_gongji(vector<Player> &players, int caster_id, bool &game_over, string &winning_team) {
    Player &caster = players[caster_id];
    if(!caster.alive) return;
    int target_id = get_lowest_alive_enemy(players, caster);
    if(target_id == -1) return;
    // Check if target can dodge
    Player &target = players[target_id];
    auto it = find(target.hand.begin(), target.hand.end(), SHANBI);
    if(it != target.hand.end()){
        // Use '闪避' to negate the attack
        target.hand.erase(it);
    }
    else{
        // Apply damage
        apply_damage(players, target_id, 1);
    }
}

// Function to execute '回复' (Heal)
void execute_huifu(vector<Player> &players, int caster_id) {
    Player &caster = players[caster_id];
    if(!caster.alive) return;
    apply_heal(players, caster_id, 1);
}

// Function to execute 'py 交易' (Py Trade)
bool execute_py_jiaoyi(vector<Player> &players, int caster_id, string &winning_team) {
    Player &caster = players[caster_id];
    if(!caster.alive) return false;
    if(caster.team == GPX){
        winning_team = "gpxnb!";
    }
    else{
        winning_team = "zyfnb!";
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Player> players(n);
    for(int i=0;i<n;i++){
        int hp, mp;
        cin >> hp >> mp;
        players[i].id = i;
        players[i].team = (i %2 ==1)? GPX : ZYF;
        players[i].max_health = hp;
        players[i].current_health = hp;
        players[i].max_mana = mp;
        players[i].current_mana = 0;
        players[i].alive = true;
        players[i].hand = vector<int>();
    }
    vector<int> deck(m);
    for(int i=0;i<m;i++) cin >> deck[i];
    int deck_ptr = 0;
    // Initial draw: each player draws 1 card
    for(int i=0;i<n;i++){
        if(deck_ptr < m){
            players[i].hand.push_back(deck[deck_ptr++]);
        }
        // Sort hand
        sort(players[i].hand.begin(), players[i].hand.end(), sort_hand);
    }
    string winning_team = "";
    bool game_over = false;
    while(!game_over){
        for(int i=0;i<n;i++){
            if(!players[i].alive) continue;
            Player &current_player = players[i];
            // Start phase
            current_player.current_mana = current_player.max_mana;
            // Draw 3 cards
            for(int j=0;j<3;j++){
                if(deck_ptr < m){
                    current_player.hand.push_back(deck[deck_ptr++]);
                }
            }
            // Sort hand
            sort(current_player.hand.begin(), current_player.hand.end(), sort_hand);
            // Play phase
            // Make a copy of hand indices to iterate since we might modify the hand during iteration
            int hand_size = current_player.hand.size();
            int index = 0;
            while(index < current_player.hand.size()){
                int card = current_player.hand[index];
                // Skip '闪避' and '反击' during play phase
                if(card == SHANBI || card == FANJI){
                    index++;
                    continue;
                }
                bool can_play = false;
                int cost = 0;
                if(card >=5 && card <=8){
                    // Spell cards except '反击' can be played if enough mana
                    if(card == FENGYIN || card == DANMU || card == YANBAO || card == FENGYIN){
                        if(card == FENGYIN){ // '封印'
                            cost =1;
                        }
                        else if(card == DANMU){
                            cost =2;
                        }
                        else if(card == YANBAO){
                            cost = current_player.current_mana; // All mana will be consumed
                        }
                        else{ // '反击' shouldn't be here
                            cost =1;
                        }
                        if(card == YANBAO){
                            // '炎爆' consumes all mana, but needs to have at least 0 mana
                            can_play = true;
                        }
                        else{
                            if(current_player.current_mana >= cost){
                                can_play = true;
                            }
                        }
                    }
                }
                else{
                    // Basic cards except '闪避'
                    can_play = true;
                }
                if(card >=5 && card <=8 && card != FENGYIN && card != DANMU && card != YANBAO && card != FANJI){
                    // Handle spell cards
                    if(card == FANJI){
                        // '反击' cannot be played during play phase
                        can_play = false;
                    }
                }
                if(can_play){
                    // Play the card
                    // Deduct mana if spell
                    if(card >=5 && card <=8){
                        if(card == YANBAO){
                            cost = current_player.current_mana;
                            current_player.current_mana =0;
                        }
                        else{
                            current_player.current_mana -= cost;
                        }
                    }
                    // Remove the card from hand
                    current_player.hand.erase(current_player.hand.begin() + index);
                    // Execute the card
                    bool py_win = false;
                    bool immediate_win = false;
                    if(card == PY_JIAOYI){
                        immediate_win = true;
                        py_win = execute_py_jiaoyi(players, i, winning_team);
                        if(py_win){
                            game_over = true;
                        }
                    }
                    else if(card == GONGJI){
                        execute_gongji(players, i, game_over, winning_team);
                    }
                    else if(card == HUIFU){
                        execute_huifu(players, i);
                    }
                    else if(card == MINGXIAN){
                        execute_mingxian(players, i);
                    }
                    else if(card == FANJI){
                        // '反击' cannot be played during play phase
                        // So do nothing
                    }
                    else if(card == DANMU){
                        // '弹幕'
                        // Check for counter '反击'
                        // '弹幕' can be countered
                        bool countered = false;
                        // Find enemies to counter
                        for(int j=0;j<n;j++){
                            Player &enemy = players[j];
                            if(enemy.team != current_player.team && enemy.alive){
                                auto it = find(enemy.hand.begin(), enemy.hand.end(), FANJI);
                                if(it != enemy.hand.end() && enemy.current_mana >=1){
                                    // Use '反击'
                                    enemy.hand.erase(it);
                                    enemy.current_mana -=1;
                                    countered = true;
                                    break;
                                }
                            }
                        }
                        if(!countered){
                            execute_danmu(players, i);
                        }
                    }
                    else if(card == YANBAO){
                        // '炎爆'
                        // Check for counter '反击'
                        // '炎爆' can be countered
                        bool countered = false;
                        for(int j=0;j<n;j++){
                            Player &enemy = players[j];
                            if(enemy.team != current_player.team && enemy.alive){
                                auto it = find(enemy.hand.begin(), enemy.hand.end(), FANJI);
                                if(it != enemy.hand.end() && enemy.current_mana >=1){
                                    // Use '反击'
                                    enemy.hand.erase(it);
                                    enemy.current_mana -=1;
                                    countered = true;
                                    break;
                                }
                            }
                        }
                        if(!countered){
                            execute_yanbao(players, i);
                        }
                    }
                    else if(card == FENGYIN){
                        // '封印'
                        // '封印' cannot be countered
                        execute_fengyin(players, i);
                    }
                    // After executing the card, check for team defeat
                    // First, check if 'py 交易' was played
                    if(immediate_win){
                        game_over = true;
                        break;
                    }
                    // Check if any team is defeated
                    bool gpx_defeated = is_team_defeated(players, GPX);
                    bool zyf_defeated = is_team_defeated(players, ZYF);
                    if(gpx_defeated){
                        winning_team = "zyfnb!";
                        game_over = true;
                        break;
                    }
                    if(zyf_defeated){
                        winning_team = "gpxnb!";
                        game_over = true;
                        break;
                    }
                }
                else{
                    index++;
                }
            }
            if(game_over) break;
            // End phase
            // Keep the first '闪避' or '反击', discard the rest
            int keep_idx = -1;
            for(int j=0; j<current_player.hand.size(); j++){
                if(current_player.hand[j] == SHANBI || current_player.hand[j] == FANJI){
                    keep_idx = j;
                    break;
                }
            }
            if(keep_idx != -1){
                // Keep the card at keep_idx, discard others
                vector<int> new_hand;
                new_hand.push_back(current_player.hand[keep_idx]);
                current_player.hand = new_hand;
            }
            else{
                // Discard all
                current_player.hand.clear();
            }
        }
    }
    // Output
    cout << winning_team << "\n";
    for(int i=0;i<n;i++){
        if(i !=0) cout << " ";
        cout << players[i].current_health;
    }
    cout << "\n";
    return 0;
}
