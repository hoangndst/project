import React, { useLayoutEffect, useState, useEffect } from 'react'
import { StyleSheet, Text, View, SafeAreaView, Button, ScrollView, TouchableOpacity } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { Avatar } from 'react-native-elements'
import CustomListItem from '../components/CustomListItem'
import { auth, db } from '../firebase'
import { Icon } from 'react-native-elements'
import ChatScreen from './ChatScreen'

const HomeScreen = ({ navigation }) => {

    const [chats, setChats] = useState([]);

    const signOutUser = () => {
        auth.signOut().then(() => {
            navigation.replace('Login');
        });
    }

    

    useEffect(() => {
        const unsubscribe = db.collection('chats').onSnapshot(snapshot => (
            setChats(snapshot.docs.map(doc => ({
                id: doc.id,
                data: doc.data()
            })))
        ))
        return unsubscribe;
    }, [])

    useLayoutEffect(() => {
        navigation.setOptions({
            
            title: "Yo"+ " " + auth.currentUser.displayName,
            headerStyle: { backgroundColor: '#2089DC'},
            headerTitleStyle: { color: "#fff", fontWeight: 'bold', flex: 1},
            headerTintColor: 'white',
            headerLeft: () => (
                <View style={{ marginLeft: 17}}>
                    <TouchableOpacity onPress={signOutUser} activeOpacity={0.5}>
                    <Avatar
                        rounded
                        source={{
                            uri: auth?.currentUser?.photoURL
                        }}
                    />
                    </TouchableOpacity>
                </View> 
            ),
            headerRight: () => (
                <View style={{
                    marginRight: 10,
                    flexDirection: 'row',
                    justifyContent: "space-between",
                    width: 70
                }}>
                    <TouchableOpacity activeOpacity={0.5}>
                        <Icon 
                            type='feather'
                            name="camera" 
                            color="white"
                            // size={24}
                        />
                        
                    </TouchableOpacity>
                    <TouchableOpacity activeOpacity={0.5}
                        onPress={() => navigation.navigate('addChat')}
                    >
                        <Icon 
                            type='feather'
                            name="user-plus" 
                            color="white"
                            // size={23}
                        />
                        
                    </TouchableOpacity>
                </View>
            ),
        });
    }, [navigation]);

    const enterChat = (id, chatName) => {
        navigation.navigate("ChatScreen", {
            id,
            chatName,
        });
    };
 
    return (
        <SafeAreaView>
            <StatusBar style='light'/>
            <ScrollView style={styles.container}>
                {chats.map(({ id, data: {chatName} }) => (
                    <CustomListItem key={id} id={id} chatName={chatName}
                        enterChat={enterChat}
                    />
                ))}
            </ScrollView>
        </SafeAreaView>
    )
}

export default HomeScreen

const styles = StyleSheet.create({
    container: {
        height: "100%",
    }
})
