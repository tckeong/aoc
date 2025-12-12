use std::fs;
use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Option<Vec<String>> {
    fs::read_to_string(path)
        .ok()?
        .lines()
        .map(|s| s.to_string())
        .collect::<Vec<String>>()
        .into()
}

#[derive(Debug)]
pub struct Shape {
    pub _tiles: Vec<Vec<u8>>,
    pub tiles_count: usize,
}

impl Shape {
    pub fn new(tiles: Vec<Vec<u8>>, tiles_count: usize) -> Shape {
        Shape {
            _tiles: tiles,
            tiles_count,
        }
    }
}

pub fn read_lines_to_shapes(lines: &Vec<String>) -> Vec<Shape> {
    let mut shapes = Vec::new();
    let mut l = 1;

    for _ in 0..6 {
        let mut tiles = Vec::new();
        let mut tiles_count = 0;

        for i in 0..3 {
            let line = &lines[l + i];
            let row = line.trim().chars();
            let mut current_row = Vec::new();

            for c in row {
                if c == '#' {
                    current_row.push(1_u8);
                    tiles_count += 1;
                } else {
                    current_row.push(0_u8);
                }
            }

            tiles.push(current_row);
        }

        shapes.push(Shape::new(tiles, tiles_count));

        l += 5;
    }

    shapes
}

#[derive(Debug)]
pub struct Region {
    pub width: usize,
    pub height: usize,
    pub quantities: Vec<usize>,
}

pub fn read_lines_to_regions(lines: &Vec<String>) -> Vec<Region> {
    let mut regions = Vec::new();
    let n = lines.len();

    for i in 30..n {
        let line = &lines[i];
        let parts = line.trim().split_whitespace().collect::<Vec<&str>>();

        let width_and_height = parts[0].chars().filter(|&c| c != ':').collect::<String>();
        let width_and_height = width_and_height.split('x').collect::<Vec<&str>>();
        let width = width_and_height[0].parse::<usize>().unwrap();
        let height = width_and_height[1].parse::<usize>().unwrap();
        let mut quantities = Vec::new();

        for part in parts.iter().skip(1) {
            let quantity = part.parse::<usize>().unwrap();
            quantities.push(quantity);
        }

        regions.push(Region {
            width,
            height,
            quantities,
        });
    }

    regions
}
