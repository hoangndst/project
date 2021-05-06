import React from 'react';
import { StyleSheet, Text, View, SafeAreaView, Image, StatusBar } from 'react-native';

export default function App() {
  const handlePress = () => console.log("Pressed");
  return (
    <SafeAreaView style={styles.container}>
      <Text onPress={handlePress}>Open up App.js to start working on your app!</Text>
      <Image style={imgStyle.icon} source={require('./assets/icon.png')}/>
      <StatusBar style='dark-content'/>
    </SafeAreaView>
  );
}

const imgStyle = StyleSheet.create({
  icon: {
    width: 50,
    height: 50
  }
});

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
