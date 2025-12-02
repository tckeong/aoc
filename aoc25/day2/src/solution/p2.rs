use crate::solution::utils::{lines_to_first_last_id, read_file_to_lines};
use std::path::Path;

pub struct SolutionP2<'a> {
    path: &'a Path,
}

impl<'a> SolutionP2<'a> {
    pub fn new(path_str: &'a str) -> Self {
        SolutionP2 {
            path: Path::new(path_str),
        }
    }

    pub fn solve(&self) -> i64 {
        let lines = read_file_to_lines(&self.path);
        let lines = lines_to_first_last_id(lines);

        let mut sum = 0;

        for (first, last) in lines {
            let invalid_ids = self.find_invalid_ids(first, last);
            sum += invalid_ids.iter().sum::<i64>();
        }

        sum
    }

    fn find_invalid_ids(&self, first: i64, last: i64) -> Vec<i64> {
        let mut invalid_ids = Vec::new();

        for id in first..=last {
            if self.is_invalid_id(id) {
                invalid_ids.push(id);
            }
        }

        invalid_ids
    }

    fn is_invalid_id(&self, id: i64) -> bool {
        let id = id.to_string();
        let id_length = id.to_string().len();

        for i in 1..id_length {
            if id_length % i != 0 {
                continue;
            }

            let pattern = &id[0..i];
            let mut constructed_id = String::new();
            for _ in 0..(id_length / i) {
                constructed_id.push_str(pattern);
            }

            if constructed_id == id {
                return true;
            }
        }

        false
    }
}
