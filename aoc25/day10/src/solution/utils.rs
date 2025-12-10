use std::fmt::Debug;
use std::fs;
use std::path::Path;

pub fn read_file_to_lines(path: &Path) -> Option<Vec<String>> {
    fs::read_to_string(path)
        .ok()?
        .lines()
        .map(|line| line.to_string())
        .collect::<Vec<String>>()
        .into()
}

pub struct Machine {
    pub indicator_lights: u16,
    pub buttons: Vec<u16>,
    pub joltage: Vec<u16>,
}

impl Machine {
    fn new(indicator_lights: u16, buttons: Vec<u16>, joltage: Vec<u16>) -> Machine {
        Machine {
            indicator_lights,
            buttons,
            joltage,
        }
    }

    fn parse_indicator_lights(s: &str) -> u16 {
        let s = s.chars().collect::<Vec<char>>();
        let n = s.len();
        let mut indicator_light = 0;
        let base = 0x8000;

        for i in 1..n - 1 {
            let current = if s[i] == '#' { base } else { 0 };
            indicator_light = indicator_light | (current >> (i - 1));
        }

        indicator_light
    }

    fn parse_button(s: &str) -> u16 {
        let n = s.len();
        let part = s[1..n - 1]
            .split(',')
            .map(|s| s.trim())
            .collect::<Vec<&str>>();
        let mut button = 0;
        let base = 0x8000;

        for p in part {
            let value = p.parse::<u32>().unwrap_or(0);
            button = button | (base >> value);
        }

        button
    }

    fn parse_buttons(s: &[&str]) -> Vec<u16> {
        let buttons = s
            .iter()
            .map(|p| Machine::parse_button(p))
            .collect::<Vec<u16>>();

        buttons
    }

    fn parse_joltage(s: &str) -> Vec<u16> {
        let n = s.len();
        let joltages = s[1..n - 1]
            .split(',')
            .map(|p| p.trim().parse::<u16>().unwrap_or(0))
            .collect::<Vec<u16>>();

        joltages
    }
}

impl Debug for Machine {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let buttons = self
            .buttons
            .iter()
            .map(|b| format!("{:016b}", b))
            .collect::<Vec<String>>();

        write!(
            f,
            "Machine {{ indicator_lights: {:016b}, buttons: {:?}, joltage: {:?} }}",
            self.indicator_lights, buttons, self.joltage
        )
    }
}

pub fn lines_to_machines(lines: &Vec<String>) -> Vec<Machine> {
    let mut machines = Vec::new();

    for line in lines {
        let parts = line
            .split_whitespace()
            .map(|s| s.trim())
            .collect::<Vec<&str>>();
        let n = parts.len();

        let indicator_lights = Machine::parse_indicator_lights(parts[0]);
        let buttons = Machine::parse_buttons(&parts[1..n - 1]);
        let joltage = Machine::parse_joltage(parts[n - 1]);

        let machine = Machine::new(indicator_lights, buttons, joltage);
        machines.push(machine);
    }

    machines
}
