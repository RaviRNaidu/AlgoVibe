# Command Chain — Geass Command Tree

An interactive web application that teaches and demonstrates the "Code Geass: Lelouch's Geass Command Tree" algorithmic problem through gameplay and visualization.

## Overview

Command Chain is a game-like educational tool for learning tree algorithms, specifically focused on:
- Building rooted command hierarchies
- Computing subtree sizes efficiently using iterative DFS
- Answering subtree queries in O(1) time after O(N) preprocessing
- Supporting up to 100,000 nodes with optimal performance

Perfect for CS students, competitive programmers, and anyone interested in tree algorithms and data structures.

## Features

### 1. Batch Mode
Process multiple INSERT and QUERY operations at once:
- Paste or upload input files
- Fast O(N) preprocessing with O(1) queries
- Real-time tree visualization with D3.js
- Color-coded nodes by depth

### 2. Game Mode (Placement Puzzle)
Interactive learning experience:
- Three difficulty levels (Easy, Medium, Hard)
- Place nodes under correct commanders
- Score system with combo multipliers
- Timer and progress tracking
- Visual feedback for correct/incorrect placements

### 3. Explain Mode
Step-by-step algorithm visualization:
- Animated DFS traversal
- Node-by-node explanation
- Subtree size computation walkthrough
- Complexity analysis display

### 4. Guide Character (Lumen)
Charismatic strategist who provides:
- Contextual hints and tips
- Encouraging feedback
- Algorithm explanations

## Algorithm Details

### Problem Statement
Given a rooted tree where ROOT represents the supreme commander (Lelouch), compute the subtree size for any node efficiently.

**Operations:**
- `INSERT X Y` - Add person X under commander Y
- `QUERY X` - Return the subtree size of person X (excluding X itself)

### Solution Approach
1. Build the tree structure from INSERT operations
2. Use iterative DFS to compute depths and subtree sizes
3. Store results for O(1) query responses

### Complexity
- **Preprocessing:** O(N) where N is the number of nodes
- **Query:** O(1) per query
- **Space:** O(N)

### Why Iterative DFS?
For large N (up to 100,000), recursive DFS may cause stack overflow. The iterative approach uses an explicit stack with ENTER/EXIT phases to safely handle deep trees.

## Sample Input/Output

### Input
```
7
INSERT A ROOT
INSERT B ROOT
INSERT C A
INSERT D A
INSERT E B
INSERT F B
INSERT G C
QUERY A
QUERY B
QUERY ROOT
```

### Output
```
3
2
7
```

### Explanation
- Node A has children C, D and grandchild G → subtree size = 3
- Node B has children E, F → subtree size = 2
- ROOT has all 7 nodes in its subtree

## Running Locally

### Prerequisites
- Node.js (v16 or higher)
- npm or yarn

### Installation
```bash
# Clone the repository
git clone <your-repo-url>
cd command-chain

# Install dependencies
npm install

# Start development server
npm run dev
```

The application will be available at `http://localhost:5173`

### Build for Production
```bash
npm run build
```

The production-ready files will be in the `dist/` directory.

## Deployment

### GitHub Pages

1. **Update vite.config.ts** (add base path):
```typescript
export default defineConfig({
  plugins: [react()],
  base: '/command-chain/', // Replace with your repo name
})
```

2. **Build and deploy**:
```bash
npm run build
git add dist -f
git commit -m "Deploy to GitHub Pages"
git subtree push --prefix dist origin gh-pages
```

3. **Enable GitHub Pages**:
   - Go to your repository Settings
   - Navigate to Pages
   - Select `gh-pages` branch as source
   - Save

Your site will be live at: `https://<username>.github.io/<repo-name>/`

### Netlify

1. **Connect your repository** to Netlify
2. **Build settings**:
   - Build command: `npm run build`
   - Publish directory: `dist`
3. **Deploy**

### Vercel

1. **Install Vercel CLI**:
```bash
npm i -g vercel
```

2. **Deploy**:
```bash
vercel
```

Follow the prompts to deploy your application.

## C++ Solution for Judge Submission

The `solution.cpp` file contains a judge-ready implementation:

### Compilation
```bash
g++ -std=c++17 -O2 -o solution solution.cpp
```

### Running
```bash
./solution < input.txt
```

### Testing with Sample Input
Create `test_input.txt`:
```
7
INSERT A ROOT
INSERT B ROOT
INSERT C A
INSERT D A
INSERT E B
INSERT F B
INSERT G C
QUERY A
QUERY B
QUERY ROOT
```

Run:
```bash
./solution < test_input.txt
```

Expected output:
```
3
2
7
```

## Project Structure

```
command-chain/
├── src/
│   ├── components/
│   │   ├── BatchMode.tsx       # Batch processing interface
│   │   ├── GameMode.tsx        # Interactive game mode
│   │   ├── ExplainMode.tsx     # Algorithm visualization
│   │   ├── TreeVisualization.tsx # D3.js tree rendering
│   │   └── GuideCharacter.tsx  # Lumen guide character
│   ├── lib/
│   │   └── graph.ts            # Core tree algorithm
│   ├── App.tsx                 # Main application
│   ├── main.tsx                # Entry point
│   └── index.css               # Global styles
├── solution.cpp                # C++ judge solution
├── package.json
├── vite.config.ts
└── README.md
```

## Technologies Used

- **React** - UI framework
- **TypeScript** - Type safety
- **D3.js** - Tree visualization
- **Tailwind CSS** - Styling
- **Vite** - Build tool
- **Lucide React** - Icons

## Performance Constraints

- Supports up to 100,000 nodes in batch mode
- Time limit: 2 seconds
- Memory limit: 256 MB
- Uses iterative DFS to avoid recursion depth issues

## Educational Use Cases

1. **Algorithm Courses**: Teach tree traversal and dynamic programming
2. **Competitive Programming**: Practice for tree-based problems
3. **Interview Prep**: Understand subtree queries and optimization
4. **Data Structures**: Visual learning of tree properties

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## License

This project is created for educational purposes.

## Acknowledgments

Inspired by the Code Geass anime series and competitive programming challenges. Built to make learning algorithms fun and interactive.

---

**Made with 💜 for CS students and algorithm enthusiasts**
