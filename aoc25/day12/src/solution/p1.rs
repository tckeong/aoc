use std::path::Path;

use crate::solution::utils;

pub struct SolutionP1<'a> {
    path: &'a Path,
}

impl SolutionP1<'_> {
    pub fn new(path: &str) -> SolutionP1<'_> {
        SolutionP1 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<u32> {
        let lines = utils::read_file_to_lines(self.path)?;
        let shapes = utils::read_lines_to_shapes(&lines);
        let regions = utils::read_lines_to_regions(&lines);
        let mut result = 0;

        for region in regions {
            let quantities = region.quantities;
            let mut total_tiles = 0;

            for i in 0..shapes.len() {
                let shape = &shapes[i];
                let quantity = quantities[i];

                total_tiles += shape.tiles_count * quantity;
            }

            if total_tiles <= region.width * region.height {
                result += 1;
            }
        }

        Some(result)
    }
}
