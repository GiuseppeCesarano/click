module.exports = {
	globDirectory: 'dist/',
	globPatterns: [
		'**/*.{js,wasm,html,webmanifest}'
	],
	swDest: 'dist/sw.js',
	ignoreURLParametersMatching: [
		/^utm_/,
		/^fbclid$/
	]
};