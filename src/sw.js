const cache_name = "click-v1";
const content_to_cache = [
  "index.html",
  "click.js",
  "click.wasm ",
  "https://raw.githubusercontent.com/JetBrains/JetBrainsMono/master/fonts/webfonts/JetBrainsMono-Bold.woff2",
];

self.addEventListener("install", (e) => {
  e.waitUntil(
    (async () => {
      const cache = await caches.open(cache_name);
      await cache.addAll(content_to_cache);
    })()
  );
});

self.addEventListener("fetch", (e) => {
  e.respondWith(
    (async () => {
      const r = await caches.match(e.request);
      if (r) {
        return r;
      }
      const response = await fetch(e.request);
      const cache = await caches.open(cache_name);
      cache.put(e.request, response.clone());
      return response;
    })()
  );
});

self.addEventListener("activate", (e) => {
  e.waitUntil(
    caches.keys().then((keyList) => {
      return Promise.all(
        keyList.map((key) => {
          if (key === cache_name) {
            return;
          }
          return caches.delete(key);
        })
      );
    })
  );

  fetch("https://api.github.com/repos/giuseppecesarano/click/commits/gh-pages")
    .then((response) => response.json())
    .then((data) => data.sha)
    .then(async (sha) => {
      if (sha != "") {
        ch = await caches.match("commit_hash");
        if (ch == undefined) {
          const cache = await caches.open(cache_name);
          cache.put("commit_hash", new Response(sha, {}));
        } else {
          const hash = await ch.text();
          if (sha != hash) {
            caches.delete(cache_name);
          }
        }
      }
    });
});
