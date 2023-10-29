#include <iostream>
#include <map>
#include <queue>
#include <vector>

int64_t limit = 100002;
uint64_t time_limit = 600;

class Track {
public:
  int64_t score_ = 0;
  int64_t track_id_ = 0;

  Track(int64_t score, int64_t track_id) : score_(score), track_id_(track_id){};

  friend class Comparator;
};

class Comparator {
public:
  bool operator()(const Track &a, const Track &b) const {
    return a.score_ > b.score_ ||
           (a.score_ == b.score_ && a.track_id_ < b.track_id_);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::map<std::string, uint64_t> ip_time;
  std::map<Track, int64_t, Comparator> map_score;
  std::map<int64_t, int64_t> map_tracks;
  std::string command, ip;
  int64_t score = 0, help_score = 0;
  int64_t track_id = 0;
  uint64_t time = 0, last_time = 0;

  for (int64_t i = 1; i < limit; i++) {
    map_tracks[i] = 0;
    map_score[Track{0, i}] = 0;
  }

  while (std::cin >> command) {
    if (command == "EXIT") {
      std::cout << "OK";
      break;
    }

    if (command == "VOTE") {
      std::cin >> ip >> track_id >> score >> time;

      if (ip_time.find(ip) == ip_time.end()) {
        ip_time[ip] = time;
        help_score = map_tracks[track_id];
        map_tracks[track_id] += score;
        map_score[Track{help_score, track_id}];
        auto node = map_score.extract(Track{help_score, track_id});
        node.key() = Track{help_score + score, track_id};
        node.mapped() = help_score + score;
        map_score.insert(std::move(node));
        std::cout << map_tracks[track_id] << '\n';
        continue;
      }
      last_time = ip_time[ip];

      if (time - last_time < time_limit) {
        std::cout << map_tracks[track_id] << '\n';
        continue;
      }
      ip_time[ip] = time;
      help_score = map_tracks[track_id];
      map_tracks[track_id] += score;
      map_score[Track{help_score, track_id}];
      auto node = map_score.extract(Track{help_score, track_id});
      node.key() = Track{help_score + score, track_id};
      node.mapped() = help_score + score;
      map_score.insert(std::move(node));
      std::cout << map_tracks[track_id] << '\n';
    } else if (command == "GET") {
      auto item = map_score.begin()->first.track_id_;
      auto item2 = map_score.begin()->first.score_;
      std::cout << item << ' ' << item2 << '\n';
      map_tracks[item] = -1;
      auto node = map_score.extract(Track{item2, item});
      node.key() = Track{-1, item};
      node.mapped() = -1;
      map_score.insert(std::move(node));
    }
  }
  return 0;
}