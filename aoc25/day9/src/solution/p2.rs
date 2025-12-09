use crate::solution::utils;
use std::path::Path;

pub struct SolutionP2<'a> {
    path: &'a Path,
}

impl SolutionP2<'_> {
    pub fn new(path: &str) -> SolutionP2<'_> {
        SolutionP2 {
            path: Path::new(path),
        }
    }

    pub fn solve(&self) -> Option<i64> {
        let lines = utils::read_file_to_lines(self.path)?;
        let tiles = utils::lines_to_tiles(&lines);
        let polygon = Polygon::new(&tiles);
        let areas = self.find_area(&polygon, &tiles);
        let max_area = areas.iter().map(|(area, _, _)| *area).max()?;

        Some(max_area)
    }

    fn find_area(&self, polygon: &Polygon, tiles: &Vec<(i64, i64)>) -> Vec<(i64, usize, usize)> {
        let n = tiles.len();
        let mut result = Vec::new();

        for i in 0..n {
            for j in (i + 1)..n {
                let (x1, y1) = tiles[i];
                let (x2, y2) = tiles[j];

                let p1 = Point::new(x1 as f64, y1 as f64);
                let p2 = Point::new(x2 as f64, y2 as f64);

                if polygon.is_rect_inside(p1, p2) {
                    let area = ((x2 - x1).abs() + 1) * ((y2 - y1).abs() + 1);
                    result.push((area, i, j));
                }
            }
        }

        result
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
struct Point {
    x: f64,
    y: f64,
}

impl Point {
    fn new(x: f64, y: f64) -> Self {
        Point { x, y }
    }
}

#[derive(Debug)]
struct Polygon {
    vertices: Vec<Point>,
}

impl Polygon {
    fn new(vertices: &Vec<(i64, i64)>) -> Self {
        let points: Vec<Point> = vertices
            .iter()
            .map(|&(x, y)| Point::new(x as f64, y as f64))
            .collect();
        Polygon { vertices: points }
    }

    fn is_rect_inside(&self, p1: Point, p2: Point) -> bool {
        // 1. Construct the 4 corners
        let min_x = p1.x.min(p2.x);
        let max_x = p1.x.max(p2.x);
        let min_y = p1.y.min(p2.y);
        let max_y = p1.y.max(p2.y);

        let corners = [
            Point::new(min_x, min_y),
            Point::new(max_x, min_y),
            Point::new(max_x, max_y),
            Point::new(min_x, max_y),
        ];

        // CHECK 1: Are all corners inside or touching the boundary?
        for corner in &corners {
            if !self.is_point_in_polygon(*corner) {
                return false;
            }
        }

        // CHECK 2: Do edges strictly cross?
        // We only fail if an edge goes through a wall. Touching/Sliding along a wall is OK.
        let rect_edges = [
            (corners[0], corners[1]),
            (corners[1], corners[2]),
            (corners[2], corners[3]),
            (corners[3], corners[0]),
        ];

        let poly_len = self.vertices.len();
        for i in 0..poly_len {
            let p_start = self.vertices[i];
            let p_end = self.vertices[(i + 1) % poly_len];

            for (r_start, r_end) in &rect_edges {
                if self.segments_cross_strictly(p_start, p_end, *r_start, *r_end) {
                    return false;
                }
            }
        }

        true
    }

    fn is_point_in_polygon(&self, p: Point) -> bool {
        let poly = &self.vertices;
        let poly_len = poly.len();

        // 1. Check if point is ON the boundary (Valid per your requirements)
        for i in 0..poly_len {
            let p1 = poly[i];
            let p2 = poly[(i + 1) % poly_len];
            if self.is_on_segment(p1, p2, p) {
                return true;
            }
        }

        // 2. Ray Casting for interior check
        let mut inside = false;
        let mut j = poly_len - 1;

        for i in 0..poly_len {
            let pi = poly[i];
            let pj = poly[j];

            if ((pi.y > p.y) != (pj.y > p.y))
                && (p.x < (pj.x - pi.x) * (p.y - pi.y) / (pj.y - pi.y) + pi.x)
            {
                inside = !inside;
            }
            j = i;
        }

        inside
    }

    // Helper: Check if point q lies exactly on segment p-r
    fn is_on_segment(&self, p: Point, r: Point, q: Point) -> bool {
        // Cross product near 0 implies collinear
        let val = (r.y - p.y) * (q.x - r.x) - (r.x - p.x) * (q.y - r.y);
        if val.abs() > 1e-9 {
            return false;
        }

        // Check bounds
        q.x <= p.x.max(r.x) && q.x >= p.x.min(r.x) && q.y <= p.y.max(r.y) && q.y >= p.y.min(r.y)
    }

    // Returns false for touching, overlapping, or T-junctions.
    fn segments_cross_strictly(&self, p1: Point, p2: Point, q1: Point, q2: Point) -> bool {
        fn orientation(p: Point, q: Point, r: Point) -> i32 {
            let val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
            if val.abs() < 1e-9 {
                return 0;
            }
            if val > 0.0 { 1 } else { -1 }
        }

        let o1 = orientation(p1, p2, q1);
        let o2 = orientation(p1, p2, q2);
        let o3 = orientation(q1, q2, p1);
        let o4 = orientation(q1, q2, p2);

        // Strict crossing requires the endpoints of one segment to be
        // on strictly opposite sides of the other segment.
        // If orientation is 0 (collinear/touching), this check fails (returns false), which is what we want.
        if (o1 != o2) && (o3 != o4) {
            // We need to exclude the 0 cases explicitly to be safe,
            // though (1 != -1) implies non-zero.
            // If any is 0, it means touching -> Return FALSE (Valid).
            if o1 == 0 || o2 == 0 || o3 == 0 || o4 == 0 {
                return false;
            }
            return true;
        }

        false
    }
}
