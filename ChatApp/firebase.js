import firebase from 'firebase/app'
import "firebase/firebase-firestore"
import "firebase/auth"

const firebaseConfig = {
    apiKey: "AIzaSyD3R0l-CxCwTHlI8JWGOGd00BY-DIx4R74",
    authDomain: "chats-506-bros.firebaseapp.com",
    projectId: "chats-506-bros",
    storageBucket: "chats-506-bros.appspot.com",
    messagingSenderId: "246906039550",
    appId: "1:246906039550:web:f1169ab6943d80daeec9af"
};

let app;
if (firebase.apps.length === 0) {
  app = firebase.initializeApp(firebaseConfig)
} else {
  app = firebase.app();
}

const db = app.firestore();
const auth = firebase.auth();

export { db, auth };